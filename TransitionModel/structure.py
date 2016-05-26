import networkx as nx
import csv


class ModelStructure:
    """
    Create facade for reading frequency matrix and transforming it
    to digraph (structure of the model) with zero-weighted edges
    """
    def __init__(self, freq_matrix_path):
        self.freq_matrix_path = freq_matrix_path
        self.freq_matrix = []
        self.__read_matrix()

    def set_up(self):
        """facade for transforming frequency matrix to weighted digraph structure
        (with adding fake "end" node)
        :return: weighted (with 0-s) directed graph
        """
        if not self.freq_matrix:
            print("Frequency matrix is empty! Cannot make transformation to digraph structure.")
            return None
        return self.__matrix_to_digraph()

    def __read_matrix(self):
        """read frequency matrix (direction is from column to row)"""
        matrix_reader = csv.reader(open(self.freq_matrix_path))
        for row in matrix_reader:
            self.freq_matrix.append([int(i) if i else None for i in row])

    def __matrix_to_digraph(self):
        """convert matrix to digraph with infinity weights
        :return: digraph (from networkx) model structure
        """
        digraph = nx.DiGraph()
        digraph.add_nodes_from(self.freq_matrix[0][1:])
        for row_ind in range(1, len(self.freq_matrix)):
            for col_ind in range(1, len(self.freq_matrix)):
                if self.freq_matrix[row_ind][col_ind]:
                    src = self.freq_matrix[0][col_ind]
                    trg = self.freq_matrix[row_ind][0]
                    digraph.add_edge(src, trg, weight=float("inf"))
        return digraph