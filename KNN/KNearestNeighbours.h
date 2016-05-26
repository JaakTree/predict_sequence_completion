#ifndef KNEARESTNEIGHBOURS_H
#define KNEARESTNEIGHBOURS_H

#include "Metrics.h"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class KNearestNeighbours {
	map<int, vector<string>> train;
	map<int, vector<string>> test;
	int prefixLength;
	int suffixLength;
	double distanceThreshold;
	string metricMethodName;
	Metrics metric;
	map<int, vector<string>> neighbours;
	//void writeToFileCorrectFormat(ofstream &fileToSave, map<int, string> idMapper, map<int, vector<string>> &data, int start, int finish = -1);
	vector<vector<double>> createDistanceMatrix();
	vector<string> findBestNeighbour(map<vector<string>, pair<int, double>>&);
	map<int, vector<string>> findBestNeighbours(vector<vector<double>> distanceMatrix);
	pair<int, double> recalculatePair(pair<int, double>, int, double);
public:

	//map<int, map<vector<string>, int>> predictSuffix(int(*calculateDistance)(vector<string>, vector<string>));

	//void saveSequence(ofstream &fileToSave, map<int, string> idMapper);

	//void saveActualSuffix(ofstream &fileToSave, map<int, string> idMapper);

	//void predictAndSaveSuffix(ofstream& fileToSave, int(*calculateDistance)(vector<string>, vector<string>), map<int, string> idMapper);
	map<int, vector<string>> getBestNeighbours(); 

	KNearestNeighbours(map<int, vector<string>> train, map<int, vector<string>> test, 
			   int prefixLength, int suffixLength, string metricMethodName, double distanceThreshold);

	
};

#endif
