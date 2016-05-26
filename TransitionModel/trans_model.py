import networkx as nx
import matplotlib.pyplot as plt
import math


from helpers.metrics import *


class TransitionModel:
    """
    Main transitional model class. Prediction is based on the most probable path
    in directed graph from last prefix event till the "fake" uniform end.
    """
    def __init__(self, train_set, digraph):
        """
        :param train_set: list of lists where each element is a trace (case) consisting from events
        :param digraph: structure (digraph from networkx) of the model
        """
        self.train = train_set
        self.digraph = digraph

    def predict(self, prefix, dist_func, threshold, plot=False):
        """facade for sequence completion prediction
        :param prefix: prefix for prediction
        :param plot: boolean variable responsible for to show or not the graph structure
        :return: result of prediction (None if it wasn't any instance in training set
        which starts from prefix)
        """
        subset = self.__training_subset_by(prefix, dist_func, threshold)
        if not subset:
            return None
        edges_weight = self.__calculate_weights(subset)
        self.__assign_weights(edges_weight)
        self.__add_fake_end(subset)
        if plot:
            self.draw_graph()
        prediction = self.__shortest_path(start_node=prefix[-1])
        self.__reset_edges()
        return prediction

    def __training_subset_by(self, prefix, dist_func, threshold):
        """Finds subset of similar traces from training set based on given metric and threshold
        :return: training instances (remaining part starting from last prefix event)
        which similar to given prefix
        """
        subset = []
        prefix_len = len(prefix)
        for case in self.train:
            if dist_func(prefix, case[:prefix_len], threshold):
                subset.append(case[prefix_len-1:])
        return subset

    def __calculate_weights(self, subset):
        """ Calculate absolute logarithm value of probabilities for each transition
        in order to convert the problem from finding the most probable to the shortest path in the graph
        :param subset: subset of suffixes (starting from the last prefix event) from training set where
        beginning coincides with given prefix
        :return: dictionary of new weights for edges
        """
        pairs_number = 0
        weights = dict()
        # calculate frequencies
        for suffix in subset:
            for i in range(len(suffix)-1):
                edge = (suffix[i], suffix[i+1])
                pairs_number += 1
                if edge in weights:
                    weights[edge] += 1
                else:
                    weights[edge] = 1
        # normalize weights and take absolute logarithm value from it
        for edge in weights:
            # here is simplified calculation of normalizer
            # as not always number of outgoing edges equal to incoming;
            # might make more accurate later
            normalized_weight = weights[edge]/len(subset)
            weights[edge] = abs(math.log(normalized_weight))
        return weights

    def __assign_weights(self, edges_weight):
        """assign converted weights to digraph (model structure)
        :param edges_weight: dictionary of weights"""
        nx.set_edge_attributes(self.digraph, "weight", edges_weight)

    def __shortest_path(self, start_node):
        """Returns the shortest path (one of them in case of several).
        :param start_node: starting node for finding the shortest path in the graph
        :return: shortest path without start (last node of prefix) and end (fake end)
        """
        try:
            paths = nx.shortest_path(self.digraph, source=start_node, target="end", weight="weight")
        except nx.NetworkXNoPath:
            print("There is no path at all for {:d} node.".format(start_node))
            return None
        prediction = paths[1:-1]
        return prediction

    def __add_fake_end(self, subset):
        """Add fake "end" node for last nodes in subset's traces
        :param subset: subset of cases
        """
        for case in subset:
            if not case:
                continue
            last_node = case[-1]
            self.digraph.add_edge(last_node, "end", weight=0.0)

    def __reset_edges(self):
        """make all edge's weights in the graph equal to infinity and delete fake end node"""
        edges = self.digraph.edges()
        for edge in edges:
            nx.set_edge_attributes(self.digraph, "weight", {edge: float("inf")})
        try:
            self.digraph.remove_node("end")
        except nx.NetworkXError:
            print("There is no \"end\" node")

    def draw_graph(self, show_infinity_edges=False):
        """Visualize graph structure
        :param show_infinity_edges: whether to show or not edges with infinity weights
        (they are in the structure based on training set, however, they are not in training subset)
        """
        pos = nx.spring_layout(self.digraph.nodes())
        # plot nodes with labels
        nx.draw_networkx_nodes(self.digraph, pos, node_size=1000)
        nx.draw_networkx_labels(self.digraph, pos)
        # choose edges and specify labels for it
        if show_infinity_edges:
            edge_list = self.digraph.edges()
        else:
            edge_list = [edge for edge in self.digraph.edges()
                     if self.digraph.get_edge_data(edge[0], edge[1])['weight'] != float("inf")]
        edge_labels = dict([((u, v,), round(d['weight'], 2)) for u, v, d in self.digraph.edges(data=True)
                            if d['weight'] != float("inf")])
        # plot edges
        nx.draw_networkx_edges(self.digraph, pos, edgelist=edge_list, edge_color='black', arrows=True)
        nx.draw_networkx_edge_labels(self.digraph, pos, edge_labels=edge_labels)
        plt.show()


