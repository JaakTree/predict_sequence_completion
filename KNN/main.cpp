#include "KNearestNeighbours.h"
#include "Separation.h"
#include "Reader.h"
#include "Filtering.h"
#include "Metrics.h"
#include "ExceptionHandler.h"
#include "InputDataUnit.h"
#include "InputParametersValidator.h"
#include "KNearestNeighboursController.h"

const int minInputLength = 5;
const char separator = ',', inColumnSeparator = '*';
const double splitPercent = 0.8, threshold = 0.8;

int main(int argc, char* argv[]) {
	InputParametersValidator validator(argc, argv, minInputLength);
	if( !validator.validateAll()) return 0;
	InputDataUnit inputData(argv[1], argv[2], argv[3], argv[4]);

	KNearestNeighboursController controller(inputData);
	controller.readData(separator);
	controller.filterData();
	controller.splitData(1.0 - stod(argv[6]));
	controller.findNeighbours(stod(argv[5]));
	controller.write(separator, inColumnSeparator);
	
	return 0;
}
