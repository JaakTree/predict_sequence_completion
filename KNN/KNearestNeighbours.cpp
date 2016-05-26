#include "KNearestNeighbours.h"

vector<vector<double>> KNearestNeighbours::createDistanceMatrix() {
	vector<vector<double>> distanceMatrix(train.size(), vector<double>(test.size()));
	int trainIndex = 0, testIndex = 0;
	for (auto &element_train : train) {
		for (auto &element_test : test) {
			vector<string> first(element_train.second.begin(), element_train.second.begin() + prefixLength),
			               second(element_test.second.begin(), element_test.second.begin() + prefixLength);
			distanceMatrix[trainIndex][testIndex++] = this->metric.calculateDistance(first, second, this->metricMethodName);
		}
		++trainIndex, testIndex = 0;
	}
	return distanceMatrix;
};

pair<int, double> KNearestNeighbours::recalculatePair(pair<int, double> p, int first, double second) {
	return make_pair(p.first + first, p.second + second);
};


vector<string> KNearestNeighbours::findBestNeighbour(map<vector<string>, pair<int, double>> &seekingNeighbours) {
	pair<int, double> bestPair = make_pair(-1, -1.0);
	vector<string> bestVector = {};
	for(auto &element: seekingNeighbours) {
		if(element.second.first > bestPair.first || (element.second.second > bestPair.second && element.second.first == bestPair.first)) {
			bestPair = element.second;
			bestVector = element.first;	
		}
	}
	return bestVector;
};

map<int, vector<string>> KNearestNeighbours::findBestNeighbours(vector<vector<double>> distanceMatrix) {
	map<int, map<vector<string>, pair<int, double>>> neighbours;
	map<int, vector<string>> bestNeighbours;
	int testIndex = 0, trainIndex = 0;
	for (auto &element_test : test) {
		for (auto &element_train : train) {
			if (distanceMatrix[trainIndex][testIndex] >= this->distanceThreshold) {
				vector<string> one;
				for (int index = prefixLength; index < prefixLength + suffixLength; ++index) {
					one.push_back(train[element_train.first][index]);
				}
	
				if (neighbours[element_test.first].find(one) != neighbours[element_test.first].end()) {
					neighbours[element_test.first][one] = recalculatePair(neighbours[element_test.first][one], 1, distanceMatrix[trainIndex][testIndex]);
				}
				else
				{
					neighbours[element_test.first][one] = recalculatePair(make_pair(0, 0.0), 1, distanceMatrix[trainIndex][testIndex]);
				}
			}
			++trainIndex;
		}
		bestNeighbours[element_test.first] = KNearestNeighbours::findBestNeighbour(neighbours[element_test.first]);
		++testIndex, trainIndex = 0;
		
	}	
	return bestNeighbours;
};

map<int, vector<string>> KNearestNeighbours::getBestNeighbours() {
	return this->neighbours;
}

KNearestNeighbours::KNearestNeighbours(map<int, vector<string>> train,
	map<int, vector<string>> test,
	int prefixLength,
	int suffixLength,
	string metricMethodName,
	double distanceThreshold
	) : train(train), test(test), prefixLength(prefixLength),
	suffixLength(suffixLength), metricMethodName(metricMethodName), distanceThreshold(distanceThreshold) {
	
	auto _distanceMatrix = KNearestNeighbours::createDistanceMatrix();
	
	this->neighbours = KNearestNeighbours::findBestNeighbours(_distanceMatrix);
}
