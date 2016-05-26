
#ifndef KNEARESTNEIGHBOURSCONTROLLER_H
#define KNEARESTNEIGHBOURSCONTROLLER_H

#include "ExceptionHandler.h"
#include "Reader.h"
#include "InputDataUnit.h"
#include "Filtering.h"
#include "Separation.h"
#include "KNearestNeighbours.h"
#include "Writer.h"

class KNearestNeighboursController {
	InputDataUnit inputData;
	map<string, vector<string>> data;
	map<int, string> idMapper;
	map<int, vector<string>> intIndexedData, train, test;
	map<int, vector<string>> neighbours;
	void setTrain(map<int, vector<string>>);
	void setTest(map<int, vector<string>>);
public:
	void readData(char separator);
	void filterData();
	void splitData(double splitPercent);
	void findNeighbours(double distanceThreshold);
	void write(char columnSeparator, char inColumnSeparator);
	KNearestNeighboursController(InputDataUnit inputData);
};


#endif
