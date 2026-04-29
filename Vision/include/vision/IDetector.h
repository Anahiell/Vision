#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
struct Detection {
	std::string className;
	float confidence;
	cv::Rect box;
};
class IDetector
{
public:
	virtual ~IDetector() = default;
	virtual std::vector<Detection> detect(const cv::Mat& frame) = 0;
};