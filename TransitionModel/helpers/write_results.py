import csv


def write_results_to(file_name, results):
    """Write list with results to specified file
    :param file_name: file name for writing results
    """
    with open(file_name, 'w+', newline='') as res_file:
        res_writer = csv.writer(res_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_NONE)
        for row in results:
            res_writer.writerow(row)
