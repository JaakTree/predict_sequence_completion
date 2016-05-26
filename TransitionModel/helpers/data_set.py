import csv
import random


class DataSet:
    """
    Class for reading data set from file and converting it to a list of traces (cases)
    The format of a file: CaseID, ActivityID
    """
    def __init__(self, data_set_path):
        self.ds_path = data_set_path
        self.data_set = self.__convert(self.__read())

    def __read(self):
        """Read data set file as it is
        :return: list of training file rows (without header)
        """
        ds_reader = csv.reader(open(self.ds_path))
        data_set = []
        for case_id, event in ds_reader:
            data_set.append((case_id, event))
        return data_set[1:]

    def __convert(self, data_set):
        """Convert rows from data file to a list of traces (cases)
        :param data_set: unprocessed rows from train file (without header)
        :return: list of traces (cases)
        """
        prev_case_id = data_set[0][0]
        current_trace = []
        traces = []
        for row in data_set:
            if prev_case_id == row[0]:
                current_trace.append(int(row[1]))
            else:
                prev_case_id = row[0]
                traces.append(current_trace)
                current_trace = list()
                current_trace.append(int(row[1]))
        return traces

    def split_data(self, test_proportion=0.25, seed=123):
        """Split randomly data on two parts: training and test (based on provided proportion)
        :param test_proportion: fraction of test samples
        :return: training and test data set
        """
        if not self.data_set:
            print("Cannot divide the data as the main data set is empty!")
            return None, None
        if (test_proportion <= 0) or (test_proportion >= 1):
            print("The value {:.2f} for test proportion is not correct. It should be more than 0 and less than 1.")
            return None, None
        random.seed(seed)
        temp_ds = self.data_set
        random.shuffle(temp_ds)
        test_len = round(test_proportion * len(temp_ds))
        test_ds = temp_ds[:test_len]
        train_ds = temp_ds[test_len:]
        return train_ds, test_ds
