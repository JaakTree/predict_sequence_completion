#include "ExceptionHandler.h"

int ExceptionHandler::handle(const char* errorMessage) {
	try {
		throw invalid_argument(errorMessage);	
	}
	catch(exception &e) {
		cout << e.what() << endl;
		return 0;	
	}
}
