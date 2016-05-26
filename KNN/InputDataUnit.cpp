#include "InputDataUnit.h"

InputDataUnit::InputDataUnit(string filename, int prefix, int suffix, string distanceMetricId) :
		filename{filename}, prefix{prefix}, suffix{suffix}, distanceMetricId{distanceMetricId}{
};

InputDataUnit::InputDataUnit(string filename, string prefix, string suffix, string distanceMetricId){
	InputDataUnit::setFilename(filename);
	InputDataUnit::setPrefix(prefix);
	InputDataUnit::setSuffix(suffix);
	InputDataUnit::setDistanceMetricId(distanceMetricId);
};


void InputDataUnit::setFilename(string filename) {
	this->filename = filename;
};

string InputDataUnit::getFilename() {
	return this->filename;
};


void InputDataUnit::setPrefix(int prefix) {
	this->prefix = prefix;
};

void InputDataUnit::setPrefix(string prefix) {
	try {
		this->prefix = stoi(prefix);
	}
	catch(exception &e) {
		this->prefix = -1;
	}
};

int InputDataUnit::getPrefix() {
	return this->prefix;
}

void InputDataUnit::setSuffix(int suffix) {
	this->suffix = suffix;
};

void InputDataUnit::setSuffix(string suffix) {
	try {
		this->suffix = stoi(suffix);
	}
	catch(exception &e) {
		this->suffix = -1;	
	}
};

int InputDataUnit::getSuffix() {
	return this->suffix;
}

void InputDataUnit::setDistanceMetricId(string distanceMetricId) {
	MetricNames metric;
	for(int i = 0; i < metric.names.size(); ++i) {
		if(distanceMetricId == metric.names[i]) {
			this->distanceMetricId = distanceMetricId;
			return;
		}
	}
	this->distanceMetricId = "";
};

string InputDataUnit::getDistanceMetricId() {
	return this->distanceMetricId;
}

bool InputDataUnit::dataUnitIsCorrect() {
	if(filename != "" && prefix != -1 && suffix != -1 && distanceMetricId != "" )
		return true;
	return false; 		
};


