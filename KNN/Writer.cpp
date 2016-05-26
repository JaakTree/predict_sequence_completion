#include "Writer.h"

void Writer::writeVector(vector<string> &outputVector, char inColumnSeparator) {
	if( outputVector.size() > 0) {
		cout << outputVector[0];
		for(int i = 1; i < outputVector.size(); ++i) {
			cout  << inColumnSeparator << outputVector[i];
		}
		return;
	}
	ExceptionHandler handler;
	handler.handle("Vector does not contain any elements!");
	
}

void Writer::write(char columnSeparator, char inColumnSeparator, int prefix, int suffix, string metricMethodName) {
	Metrics metric;

	for(auto &index_id: idMapper) {
		if(test.find(index_id.first) != test.end() && neighbours[index_id.first].size() > 0) {
			vector<string> actualSuffix;	
			if(test[index_id.first].size() == prefix + suffix) {
				actualSuffix = {test[index_id.first].begin() + prefix, test[index_id.first].end()};
			}
			else { 
				actualSuffix = {test[index_id.first].begin() + prefix, test[index_id.first].begin() + prefix + suffix};
			}
			
			cout << metric.calculateDistance(neighbours[index_id.first], actualSuffix, "lv") << columnSeparator;
			cout << metric.calculateDistance(neighbours[index_id.first], actualSuffix, "dl") << columnSeparator;
			cout << metric.calculateDistance(neighbours[index_id.first], actualSuffix, "jc") << columnSeparator;
			cout << metric.calculateDistance(neighbours[index_id.first], actualSuffix, "hm") << columnSeparator;	

			writeVector(actualSuffix, columnSeparator);

			cout << columnSeparator << inColumnSeparator << columnSeparator;

			writeVector(neighbours[index_id.first], columnSeparator);
			
			cout << columnSeparator;
			cout << index_id.second << endl;
		}
	}
	
}

Writer::Writer(map<int, string> idMapper, map<int, vector<string>> neighbours, map<int, vector<string>> test, string filename):
	idMapper{idMapper}, neighbours{neighbours}, test{test}, filename{filename} {
}

Writer::~Writer() {
} 
