#ifndef INPUTPARAMETERSVALIDATOR_H
#define INPUTPARAMETERSVALIDATOR_H

#include "ExceptionHandler.h"
#include "InputDataUnit.h"
#include <cstring>
#include <cstdlib>

class InputParametersValidator {
	int numberArguments;
	char** arguments;
	int minNumberParameters;
	bool validateNumberParameters();
	bool validateParameters();
public:
	bool validateAll();
	InputParametersValidator(int argc, char* argv[], int minNumberParameters);
	~InputParametersValidator();
};

#endif
