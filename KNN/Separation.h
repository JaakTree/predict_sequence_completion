#ifndef SEPARATION_H
#define SEPARATION_H

#include <iostream>
#include<string>
#include<map>
#include<set>
#include <vector>
#include <algorithm>

using namespace std;

class Separation {
	map<int, vector<string>> data, train, test;
	double trainPercentSize;
	set<int> generateTrainIndexes();
	void createTrain(set<int> trainIndexes);
	void createTest(set<int> trainIndexes);
public:
	map<int, vector<string>> getTrain();
	map<int, vector<string>> getTest();
	void doSeparation();
	Separation(map<int, vector<string>> data, double trainPercentSize);
};

#endif