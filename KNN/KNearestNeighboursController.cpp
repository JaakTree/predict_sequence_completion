#include "KNearestNeighboursController.h"

KNearestNeighboursController::KNearestNeighboursController(InputDataUnit inputData):inputData(inputData) {
}

void KNearestNeighboursController::readData(char separator) {
	Reader reader(inputData.getFilename());
	data = reader.getDataWithoutHeader(separator);
};


void KNearestNeighboursController::filterData() {
	Filtering filtering(this->data, inputData.getPrefix(), inputData.getSuffix());
	this->intIndexedData = filtering.filterDataByLength();
	this->idMapper = filtering.getIdMapper();	
};

void KNearestNeighboursController::splitData(double splitPercent) {
	Separation separation(this->intIndexedData, splitPercent);
	separation.doSeparation();
	KNearestNeighboursController::setTrain(separation.getTrain());
	KNearestNeighboursController::setTest(separation.getTest());		
};

void KNearestNeighboursController::setTrain(map<int, vector<string>> train) {
	this->train = train;
};

void KNearestNeighboursController::setTest(map<int, vector<string>> test) {
	this->test = test;
};

void KNearestNeighboursController::findNeighbours(double distanceThreshold) {
	KNearestNeighbours knn(this->train, this->test, this->inputData.getPrefix(), this->inputData.getSuffix(), this->inputData.getDistanceMetricId(), distanceThreshold);	
	this->neighbours = knn.getBestNeighbours();
}

void KNearestNeighboursController::write(char columnSeparator, char inColumnSeparator) {
	string filename = inputData.getFilename() + "_" + to_string(inputData.getPrefix()) + "_" + to_string(inputData.getSuffix()) + "_" + inputData.getDistanceMetricId();
	Writer writer(this->idMapper, this->neighbours, this->test, filename);
	
	writer.write(columnSeparator, inColumnSeparator, inputData.getPrefix(), inputData.getSuffix(), inputData.getDistanceMetricId());	
}
