#include "Metrics.h"

void Metrics::setTest(vector<string> test) {
	this->test = test;
}

void Metrics::setTrain(vector<string> train) {
	this->train = train;
}

void Metrics::setNormaliseLength(int normaliseLength) {
	this->normaliseLength = normaliseLength;
}

int Metrics::getNormaliseLength() {
	return this->normaliseLength;
}

set<string> Metrics::createSetFromVector(vector<string> &v) {
	set<string> setFromVector{ v.begin(), v.end() };
	return setFromVector;
}

set<string> Metrics::intersectSets(set<string>& suffixTrain, set<string> &suffixTest) {
	set<string> intersectedSuffix;
	for (auto &element : suffixTrain) {
		if( suffixTest.find(element) != suffixTest.end())
			intersectedSuffix.insert(element);
	}
	return intersectedSuffix;
}

double Metrics::HammingDistance() {
	int distance = 0;
	for (int i = 0; i < test.size(); ++i) {
		distance += ((test[i] == train[i]) ? (0) : (1));
	}
	return 1. - (double)distance/normaliseLength;
}

double Metrics::ReverseJaccardDistance() {
	set<string> trainSet = createSetFromVector(train), testSet = createSetFromVector(test), 
				intersectSet = intersectSets(trainSet, testSet);
	return (double)intersectSet.size() / (trainSet.size() + testSet.size() - intersectSet.size());
}

double Metrics::DamerauLevenshteinDistance() {
	vector<vector<int>> distanceMatrix(test.size() + 1, vector<int>(train.size() + 1));
	for (int i = 0; i <= test.size(); ++i) distanceMatrix[i][0] = i;
	for (int i = 0; i <= train.size(); ++i) distanceMatrix[0][i] = i;
	for (int i = 1; i <= test.size(); ++i) {
		for (int j = 1; j <= train.size(); ++j) {
			distanceMatrix[i][j] = min({ distanceMatrix[i - 1][j] + 1,
				distanceMatrix[i][j - 1] + 1,
				distanceMatrix[i - 1][j - 1] + ((test[i - 1] == train[j - 1]) ? (0) : (1))});
			if (i > 1 && j > 1 && i < test.size() && j < train.size() && 
				test[i] == train[j - 1] && test[i - 1] == train[j])
				distanceMatrix[i][j] = min(distanceMatrix[i][j], distanceMatrix[i - 2][j - 2] + 1);
		}
	}
	return 1. - (double)distanceMatrix[test.size()][train.size()] / normaliseLength;
}

double Metrics::EditDistance() {
	vector<vector<int>> distanceMatrix(test.size() + 1, vector<int>(train.size() + 1));
	for (int i = 0; i <= test.size(); ++i) distanceMatrix[i][0] = i;
	for (int i = 1; i <= train.size(); ++i) distanceMatrix[0][i] = i;
	for (int i = 1; i <= test.size(); ++i) {
		for (int j = 1; j <= train.size(); ++j) {
			distanceMatrix[i][j] = min({distanceMatrix[i - 1][j] + 1, 
										distanceMatrix[i][j - 1] + 1, 
										distanceMatrix[i - 1][j - 1] + ((test[i - 1] == train[j - 1]) ? 0 : 1)});
		}
	}
	return 1. - (double)distanceMatrix[test.size()][train.size()]/normaliseLength;
}

vector<string> Metrics::createVectorFromString(string &suffix) {
	vector<string> suffixVector;
	for (int i = 0; i < suffix.length(); ++i) {
		suffixVector.push_back(to_string(suffix[i]));
	}
	return suffixVector;
}

void Metrics::testMetrics(string suffixOne, string suffixTwo, vector<double>& expected) {
	vector<string> suffixVectorOne = createVectorFromString(suffixOne),
				   suffixVectorTwo = createVectorFromString(suffixTwo);
	setTrain(suffixVectorOne);
	setTest(suffixVectorTwo);
	setNormaliseLength(suffixOne.length());
}

Metrics::Metrics(vector<string> test, vector<string> train, int normaliseLength):test{test}, train{train} {
	this->normaliseLength = test.size();
}

Metrics::Metrics() {

}

double Metrics::calculateDistance(vector<string> train, vector<string> test, string methodName) {
	Metrics::setTrain(train);
	Metrics::setTest(test);
	Metrics::setNormaliseLength(test.size());
	if(methodName == "lv")
		return Metrics::EditDistance();
	else if(methodName == "hm")
		return Metrics::HammingDistance();
	else if(methodName == "jc")
		return Metrics::ReverseJaccardDistance(); 
	else if(methodName == "dl")
		return Metrics::DamerauLevenshteinDistance();

	ExceptionHandler handler;
	handler.handle("Incorrect metric name.");	
	return 0.0;	
}
