#include "Reader.h"

vector<string> Reader::splitLineBySeparator(string line, char separator) {
	int startIndex = 0;
	vector<string> columns; 		
	for (int index = 0; index < line.length(); ++index) {
		if (line[index] == separator || index == line.length() - 1) {
			columns.push_back(line.substr(startIndex, index - startIndex));
			startIndex = index + 1;
		}
	}
	if(columns.size() < 2) {
		ExceptionHandler handler;
		handler.handle("Too few columns");
		return columns;
	}
	return {columns[0], columns[1]};
}

void Reader::addColumns(vector<string> columns) {
	if (data.find(columns[0]) != data.end()) {
		data[columns[0]].push_back(columns[1]);
		return;
	}
	vector<string> oneElementVector{ columns[1] };
	data[columns[0]] = oneElementVector;
}


map<string, vector<string>> Reader::getDataWithHeader(char separator) {
	string line;
	getline(inputFileStream, line);
	return Reader::getDataWithoutHeader(separator);
}


map<string, vector<string>> Reader::getDataWithoutHeader(char separator) {
	string line;
	vector<string> columns;
	while (getline(inputFileStream, line)) {
		string destinationString;
		transform(line.begin(), line.end(), destinationString.begin(), ::tolower);	
		if(destinationString.find("case") != string::npos)
			continue;
		columns = splitLineBySeparator(line, separator);
		addColumns(columns);
	}
	return data;
}

Reader::Reader(string filename) :filename(filename) {
	inputFileStream.open(filename);
};

Reader::~Reader() { 
	inputFileStream.close();
}
