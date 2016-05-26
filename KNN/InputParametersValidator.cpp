#include "InputParametersValidator.h"

InputParametersValidator::InputParametersValidator(int argc, char* argv[], int minNumberParameters): numberArguments{argc}, minNumberParameters{minNumberParameters} {
	arguments = new char* [argc];
	for(int i = 0; i < argc; ++i) {
		arguments[i] = new char [strlen(argv[i])];
		arguments[i] = argv[i];
	}
};

InputParametersValidator::~InputParametersValidator() {
	if(arguments != NULL)
		delete [] arguments;
}

bool InputParametersValidator::validateAll() {
	bool validity = true;
	validity &= InputParametersValidator::validateNumberParameters();
	if( !validity ) return validity;
	validity &= InputParametersValidator::validateParameters();
	return validity;
};

bool InputParametersValidator::validateNumberParameters() {
	if( numberArguments < minNumberParameters ) {
		ExceptionHandler handler;
		handler.handle("Too little parameters");
		return false;
	}
	return true;
}


bool InputParametersValidator::validateParameters() {
	InputDataUnit inputData(arguments[1], arguments[2], arguments[3], arguments[4]);
	if(!inputData.dataUnitIsCorrect()) {
		ExceptionHandler handler;
		handler.handle("Incorrect parameters type");
		return false;
	}
	return true;
}

