#include "Filtering.h"


map<int, string> Filtering::getIdMapper() {
	return this->idMapper;
}

set<string> Filtering::collectShortSequencesIndexes() {
	set<string> indexesForRemoval;
	for (auto &element : data) {
		if (element.second.size() < minimalSequenceLength)
			indexesForRemoval.insert(element.first);
	}
	return indexesForRemoval;
}

void Filtering::removeShortSequences() {
	set<string> indexesForRemoval = collectShortSequencesIndexes();
	for (auto &remove_element : indexesForRemoval)
		this->data.erase(remove_element);
}

map<int, vector<string>> Filtering::filterDataByLength() {
	removeShortSequences();

	map<int, vector<string>> indexedData;
	int index = 0;
	for (auto &element : data) {
		idMapper[index] = element.first;
		indexedData[index++] = element.second;
	}
	return indexedData;
}

Filtering::Filtering(map<string, vector<string>> data, int prefixLength, int suffixLength) :data{ data },
	minimalSequenceLength(prefixLength + suffixLength){
};
