#ifndef FILTERING_H
#define FILTERING_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Filtering {
	map<string, vector<string>> data;
	// make work with id much easier, save convertion between new and initial ids.
	map<int, string> idMapper;
	int minimalSequenceLength;
	void removeShortSequences();
	set<string> collectShortSequencesIndexes();
public:
	map<int, string> getIdMapper();
	map<int, vector<string>> filterDataByLength();
	Filtering(map<string, vector<string>> data, int prefixLength, int suffixLength);

};

#endif
