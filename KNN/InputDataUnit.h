#ifndef INPUTDATAUNIT_H
#define INPUTDATAUNIT_H

#include <string>
#include <vector>
#include "ExceptionHandler.h"

using namespace std;

struct MetricNames {
	public:
	vector<string> names = {"dl", "hm", "lv", "jc"};
};

class InputDataUnit{
	string filename;
	int prefix;
	int suffix;
	string distanceMetricId;
	public:	
	bool dataUnitIsCorrect();
	void setFilename(string filename);
	string getFilename();
	void setPrefix(string prefix);
	void setPrefix(int prefix);
	int getPrefix();
	void setSuffix(string suffix);
	void setSuffix(int suffix);
	int getSuffix();
	void setDistanceMetricId(string distanceMetricId);
	string getDistanceMetricId();
	InputDataUnit(string filename, string prefix, string suffix, string distanceMetricId);
	InputDataUnit(string filename, int prefix, int suffix, string distanceMetricId);
};

#endif
