#include "Separation.h"

map<int, vector<string>> Separation::getTrain() {
	return this->train;
}

map<int, vector<string>> Separation::getTest() {
	return this->test;
}

set<int> Separation::generateTrainIndexes() {
	set<int> trainIndexes;
	while ((double)trainIndexes.size() < trainPercentSize) {
		trainIndexes.insert(rand() % data.size());
	}
	return trainIndexes;
}

void Separation::createTrain(set<int> trainIndexes) {
	for (auto &index : trainIndexes) {
		train[index] = data[index];
	}
}

void Separation::createTest(set<int> trainIndexes) {
	for (auto &element : data) {
		if (trainIndexes.find(element.first) == trainIndexes.end())
			test[element.first] = data[element.first];
	}
}

void Separation::doSeparation() {
	set<int> trainIndexes = generateTrainIndexes();
	createTrain(trainIndexes);
	createTest(trainIndexes);
}

Separation::Separation(map<int, vector<string>> data, double trainPercentSize) :data(data) {
	this->trainPercentSize = (ceil(trainPercentSize*data.size()));
}
