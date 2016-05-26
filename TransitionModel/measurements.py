import csv
import time


from helpers.data_set import DataSet
from helpers.metrics import *
from helpers.write_results import *
from trans_model import TransitionModel
from structure import ModelStructure


def experiment(ds_path, frequency_matrix_path, dist_func, threshold, test_proportion, prefix_len, prediction_len=-1):
    """Conduct measurements for Transitional_model
    :param prefix_len: length of prefix for prediction
    :param ds_path: path to data set
    :param frequency_matrix_path: path to frequency transition matrix
    :return: list of accuracy metrics for test samples
    """
    ds = DataSet(data_set_path=ds_path)
    train_set, test_set = ds.split_data(test_proportion)
    structure = ModelStructure(freq_matrix_path=frequency_matrix_path)
    digraph = structure.set_up()
    model = TransitionModel(train_set=train_set, digraph=digraph)
    results = []
    for case in test_set:
        # filter too short instances
        if len(case) < prefix_len + prediction_len:
            continue
        prefix = case[:prefix_len]
        suffix = case[prefix_len:]
        prediction = model.predict(prefix, dist_func, threshold, plot=False)
        if not prediction:
            continue
        if prediction_len == -1:
            prediction_len = len(suffix)
        res = accuracy(first=prediction[:prediction_len], second=suffix[:prediction_len])
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
        method = row[1]
        if method == 'lv':
            dist_func = is_similar_by_levenstein
        elif method == 'dl':
            dist_func = is_similar_by_damerau_levenstein
        else:
            print("Unidentified method!", "Skip parameters set #{:d}".format(num))
            continue
        threshold = float(row[2])
        test_proportion = float(row[3])
        prefixes_len = [int(x) for x in row[4].split(";")]
        suffixes_len = [int(x) for x in row[5].split(";")]
        param_set.append([file_name, dist_func, threshold, test_proportion, prefixes_len, suffixes_len, method])
    return param_set


if __name__ == "__main__":
    param_sets = read_experiment_parameters("../evaluation/plan.csv")
    for ind, param in enumerate(param_sets, 1):
        start = time.clock()
        base_file_name = param[0]
        pref_lens = param[4]
        pred_lens = param[5]
        print("Evaluation for {:s} file".format(base_file_name))
        try:
            for pref_len in pref_lens:
                for pred_len in pred_lens:
                    results = experiment(ds_path="../data/" + base_file_name,
                    frequency_matrix_path="../data/case_freqs/" + base_file_name,
                    test_proportion=param[3], dist_func=param[1],
                    threshold=param[2], prefix_len=pref_len, prediction_len=pred_len)
                    result_file = "../results/Transitional_model/{:s}_{:s}_{:d}_{:d}_".format(param[6],
                                                      str(param[2]), pref_len,
                                                      pred_len) \
                          + base_file_name
                    if results:
                        write_results_to(result_file, results)
                    else:
                        print("There is no results for {:d} param set".format(ind))
        except:
            print("Error for {:d} param set!!! Skip process it".format(ind))
            continue
        end = time.clock()
        print(end-start)