#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H
#include <stdexcept>
#include <iostream>

using namespace std;

class ExceptionHandler {
public: 
	int handle(const char *errorMessage);
};

#endif
