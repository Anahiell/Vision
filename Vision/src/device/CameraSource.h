#pragma once
#include <vision/logger.h>
#include <opencv2/opencv.hpp>
#include <chrono>

class CameraSource {
	Logger& log;
	std::vector<int> apis = { cv::CAP_DSHOW, cv::CAP_MSMF, cv::CAP_ANY };

private:
	double fps = 0.0;
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	int frameCount = 0;
	cv::VideoCapture cap;
	int emptyFrameCount = 0;
public:
	CameraSource(Logger& log);
	bool openCamera(int index);
	void closeCamera();
	bool isCameraOpen();
	cv::Mat captureFrame();
};