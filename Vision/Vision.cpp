// Vision.cpp : Defines the entry point for the application.
//

#include "Vision.h"
#include "vision/logger.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	Logger::info("This is an info message.");

	return 0;
}
