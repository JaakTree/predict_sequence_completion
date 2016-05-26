import random
import csv
import time


from helpers.data_set import DataSet
from helpers.metrics import *
from helpers.write_results import *
from TransitionModel.structure import ModelStructure


def random_prediction(matrix, start, prediction_len):
    current_node = start
    prediction = []
    for _ in range(prediction_len):
        current_node = get_rnd_neighbors(matrix, current_node)
        if not current_node:
            print("Stopped prediction as got to the end node")
            break
        prediction.append(current_node)
    return prediction


def get_rnd_neighbors(matrix, node):
    neighbors = []
    col_ind = matrix[0].index(node)
    for row_ind, row in enumerate(matrix):
        if row[col_ind]:
            neighbor = matrix[row_ind][0]
            neighbors.append(neighbor)
    if not neighbors:
        return None
    return random.choice(neighbors)


def experiment(ds_path, frequency_matrix_path, prefix_len, test_proportion, prediction_len=-1):
    ds = DataSet(data_set_path=ds_path)
    train_set, test_set = ds.split_data(test_proportion)
    matrix = ModelStructure(freq_matrix_path=frequency_matrix_path).freq_matrix
    results = []
    for indx, case in enumerate(test_set):
        print("test sample: {:d}".format(indx))
        # filter too short instances
        if len(case) < prefix_len + prediction_len:
            continue
        if prediction_len == -1:
            prediction_len = len(suffix)

        suffix = case[prefix_len:]
        prediction = random_prediction(matrix, case[prefix_len-1], prediction_len)
        if not prediction:
            continue
        res = accuracy(first=prediction[:prediction_len], second=suffix[:prediction_len])
        print(res)
        res = [res[0], res[1], res[2]] + suffix[:prediction_len] + ["*"] + prediction[:prediction_len]
        results.append(res)
    return results


def read_experiment_parameters(file_path):
    """Read parameters for conducting automated experiment
     :param file_path: path to file with parameters
     :return: list of parameter's sets
    """
    param_reader = csv.reader(open(file_path))
    rows_in_file = []
    for row in param_reader:
        rows_in_file.append(row)

    param_set = []
    for num, row in enumerate(rows_in_file[1:], 1):
        file_name = row[0]
        prefixes_len = [int(x) for x in row[1].split(";")]
        suffixes_len = [int(x) for x in row[2].split(";")]
        param_set.append([file_name, prefixes_len, suffixes_len])
    return param_set


if __name__ == "__main__":
    param_sets = read_experiment_parameters("../evaluation/plan_random.csv")
    for ind, param in enumerate(param_sets, 1):
        start = time.clock()
        base_file_name = param[0]
        pref_lens = param[1]
        pred_lens = param[2]
        print("Evaluation for {:s} file".format(base_file_name))
        for pref_len in pref_lens:
            for pred_len in pred_lens:
                results = experiment(ds_path="../data/" + base_file_name,
                                 frequency_matrix_path="../data/case_freqs/" + base_file_name, test_proportion=0.2,
                                 prefix_len=pref_len, prediction_len=pred_len)
                result_file = "../results/Random_model/rnd_{:d}_{:d}_".format(pref_len, pred_len) + \
                          base_file_name
                if results:
                    write_results_to(result_file, results)
                else:
                    print("There is no results for {:d} param set".format(ind))
        end = time.clock()
        print(end-start)