#ifndef READER_H
#define READER_H

#include "ExceptionHandler.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <locale>
#include <algorithm>

using namespace std;

class Reader {
	map<string, vector<string>> data;
	string filename;
	ifstream inputFileStream;
	vector<string> splitLineBySeparator(string line, char separator);
	void addColumns(vector<string>);
public:
	

	map<string, vector<string>> getDataWithHeader(char separator);
	map<string, vector<string>> getDataWithoutHeader(char separator);

	Reader(string filename);

	~Reader();
};

#endif
