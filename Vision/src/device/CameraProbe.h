#pragma once
#include <vision/logger.h>

class CameraProbe {
	Logger& log;
private:
	std::vector<int> cameraList;
public:
	CameraProbe(Logger& log);

	void probeCameras();

	~CameraProbe();

};