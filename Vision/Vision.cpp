// Vision.cpp : Defines the entry point for the application.
//

#include "Vision.h"
#include "vision/logger.h"

using namespace std;

int main()
{
	Logger log = Logger();
	cout << "Hello CMake." << endl;
	log.info("This is an info message [INFO] - need to be blue");
	log.error("This is an error message. [ERROR] - need to be red color");
	log.warning("This is an warning message. [WARNING] = need to be Yellow color");

	return 0;
}
