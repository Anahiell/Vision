#include "vision/YoloDetector.h"

YoloDetector::YoloDetector()
{
	std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
	if (!std::filesystem::exists(configPath))
		throw std::runtime_error("Config not found: " + configPath);

	if (!std::filesystem::exists(modelPath))
		throw std::runtime_error("Weights not found: " + modelPath);

	if (!std::filesystem::exists(namesPath))
		throw std::runtime_error("Names not found: " + namesPath);

	net = cv::dnn::readNetFromDarknet(configPath, modelPath);
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	std::ifstream file(namesPath);
	std::string line;

	while (getline(file, line)) {
		classes.push_back(line);
	}
}

std::vector <Detection> YoloDetector::detect(const cv::Mat& frame)
{
	std::vector<Detection> result;
	if (frame.empty() || net.empty() || classes.empty()) {
		return result;
	}
	std::vector<int>classIds;
	std::vector<float>confidences;
	std::vector<cv::Rect>boxes;
	cv::Mat blob;

	cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(416, 416), cv::Scalar(), true, false);
	net.setInput(blob);

	std::vector <cv::Mat> outputs;
	net.forward(outputs, net.getUnconnectedOutLayersNames());

	for (const auto& output : outputs) {
		for (int i = 0;i < output.rows; i++) {

			float* data = (float*)output.data + i * output.cols;

			float confidence = data[4];
			if (confidence > 0.5) {

				int classId = std::max_element(data + 5, data + output.cols) - (data + 5);
				float score = data[5 + classId];

				if (score > 0.5) {

					int centerX = (int)(data[0] * frame.cols);
					int centerY = (int)(data[1] * frame.rows);
					int width = (int)(data[2] * frame.cols);
					int hieght = (int)(data[3] * frame.rows);

					int x = centerX - width / 2;
					int y = centerY - hieght / 2;

					boxes.push_back(cv::Rect(x,y,width,hieght));
					classIds.push_back(classId);
					confidences.push_back(score);
				}
			}
		}
	}
	std::vector<int>indices;
	cv::dnn::NMSBoxes(boxes,confidences,0.5f,0.4f,indices);
	for (int idx : indices) {
		Detection det;
		det.className = classes[classIds[idx]];
		det.confidence = confidences[idx];
		det.box = boxes[idx];

		result.push_back(det);
	}
	return result;
}