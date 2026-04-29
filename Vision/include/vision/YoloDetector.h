#pragma once
#include <iostream>
#include<fstream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <stdexcept>
#include "vision/IDetector.h"

class YoloDetector : public IDetector
{
public:
	YoloDetector();
	std::vector<Detection> detect(const cv::Mat& frame) override;

private:
	cv::dnn::Net net;
	std::string modelPath = "models/yolo/yolov3.weights";
	std::string configPath = "models/yolo/yolov3.cfg";
	std::string namesPath = "models/yolo/coco.names";
	std::vector<std::string> classes;
	
};

