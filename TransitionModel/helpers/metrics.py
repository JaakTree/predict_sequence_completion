import distance
from helpers.damerau_levenshtein import damerau_levenshtein_distance


def accuracy(first, second):
    """Calculates similarity metrics for two lists (the order of parameters doesn't matter)
    :param first: list with predicted events
    :param second: list with true events
    :return: tuple of specified accuracy metrics (similarities): normalized Levenshtein and Damerau-Levenstein, Jaccard
    """
    n_levenstein = 1 - distance.nlevenshtein(first, second)
    n_damerau_levenshtein = (1 - damerau_levenshtein_distance(first, second)) / max(len(first), len(second))
    jaccard = 1 - distance.jaccard(first, second)
    return n_levenstein, n_damerau_levenshtein, jaccard


def is_similar_by_levenstein(first, second, threshold):
    """Check rather two lists are similar by Levenstein similarity metrics up to threshold
    :param first: one of the lists
    :param second: another list
    :param threshold: similarity threshold
    :return: boolean value is elements are similar up to threshold
    """
    if (1 - distance.nlevenshtein(first, second)) >= threshold:
        return True
    return False


def is_similar_by_damerau_levenstein(first, second, threshold):
    """Check rather two lists are similar by Damerau-Levenstein similarity metrics up to threshold
    :param first: one of the lists
    :param second: another list
    :param threshold: similarity threshold
    :return: boolean value is elements are similar up to threshold
    """
    n_damerau_levenshtein = (1 - damerau_levenshtein_distance(first, second)) / max(len(first), len(second))
    if n_damerau_levenshtein >= threshold:
        return True
    return False


def is_near_by_hamming(first, second, threshold):
    """Check rather two lists are near by Hamming distance up to threshold
    :param first: one of the lists
    :param second: another list
    :param threshold: similarity threshold
    :return: boolean value is elements are similar up to threshold
    """
    if len(first) != len(second):
        first = " ".join([str(x) for x in first])
        second = " ".join([str(x) for x in second])
        print("Cannot apply the hamming distance to {:s} and {:s} due difference length".format(first, second))
        return None
    if distance.hamming(first, second) <= threshold:
        return True
    return False
