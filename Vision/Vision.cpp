// Vision.cpp : Defines the entry point for the application.
//

#include "Vision.h"
#include "vision/logger.h"
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
	Logger log = Logger();
	cout << "Hello CMake." << endl;
	log.info("This is an info message [INFO] - need to be blue");
	log.error("This is an error message. [ERROR] - need to be red color");
	log.warning("This is an warning message. [WARNING] = need to be Yellow color");

	cv::VideoCapture cap(0); // Open the default camera
	if (!cap.isOpened()) {
		log.error("Error: Could not open camera.");
		return -1;
	}
	cv::Mat frame;
	while (true) {
		cap >> frame; // Capture a new frame
		if (frame.empty()) {
			log.error("Error: Could not capture frame.");
			break;
		}
		cv::imshow("Camera Feed", frame); // Display the captured frame
		if (cv::waitKey(30) >= 0) break; // Exit on any key press
	}
	return 0;
}
