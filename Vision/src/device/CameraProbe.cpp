#include "CameraProbe.h"
#include <opencv2/opencv.hpp>

CameraProbe::CameraProbe(Logger& log)
	: log(log)
{
	log.info("Initializing CameraProbe...");
}

CameraProbe::CameraProbe(int maxIdex, Logger& log)
	: log(log), maxIdex(maxIdex)
{
	this->maxIdex = maxIdex;
	log.info("Initializing CameraProbe with max index: " + std::to_string(maxIdex));
}

std::vector<int> CameraProbe::probeCameras()
{
	std::vector<int> cameraList;
	cv::VideoCapture cap;

	for(int i =0; i<maxIdex; i++){
		log.info("Probing camera index: " + std::to_string(i));
		cap.open(i,cv::CAP_MSMF);
		if (cap.isOpened()) {
			log.info("Camera found at index: " + std::to_string(i));
			cameraList.push_back(i);
		}
		else {
			log.warning("No camera found at index: " + std::to_string(i));
		}
	}
	cap.release();
	return cameraList;
}

