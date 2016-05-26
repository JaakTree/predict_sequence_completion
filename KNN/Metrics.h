#ifndef METRICS_H
#define METRICS_H

#include "ExceptionHandler.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <iostream>


using namespace std;

class Metrics {
	vector<string> train, test;
	int normaliseLength;
	set<string> createSetFromVector(vector<string>&);
	set<string> intersectSets(set<string> &test, set<string> &train);
public:

	vector<string> createVectorFromString(string&);

	void setNormaliseLength(int normaliseLength);
	
	int getNormaliseLength();

	void setTrain(vector<string> train);

	void setTest(vector<string> test);
	
	double HammingDistance();
	
	double ReverseJaccardDistance();

	double DamerauLevenshteinDistance();

	double EditDistance();
	
	double calculateDistance(vector<string>, vector<string>, string methodName);

	Metrics(vector<string>, vector<string>, int normaliseLength);
	
	Metrics();

	void testMetrics(string suffixOne, string suffixTwo, vector<double>&);
};

#endif
