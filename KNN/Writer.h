#ifndef WRITER_H
#define WRITER_H

#include "Metrics.h"
#include "ExceptionHandler.h"
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;


class Writer {
	map<int, string> idMapper;
	map<int, vector<string>> neighbours;
	map<int, vector<string>> test;
	string filename;
	void writeVector(vector<string>&, char);	
public:
	void write(char columnSeparator, char inColumnSeparator, int prefix, int suffix, string metricMethodName);
	Writer(map<int, string> idMapper, map<int, vector<string>> neighbours, map<int, vector<string>> test, string filename);
	~Writer();
};

#endif
