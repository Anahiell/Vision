#pragma once
#include <vision/logger.h>

class CameraProbe {
	Logger& log;
public:
	int maxIdex = 5; // Maximum camera index to probe
	CameraProbe() = delete; // Delete default constructor
	CameraProbe(Logger& log);
	CameraProbe(int maxIdex, Logger& log);


	std::vector<int> probeCameras();
};