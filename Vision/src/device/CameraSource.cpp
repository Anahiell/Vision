#include "CameraSource.h"

CameraSource::CameraSource(Logger& log)
	: log(log)
{
	fps = 0;
	frameCount = 0;
	log.info("Initializing CameraSource...");
}

bool CameraSource::openCamera(int index)
{
	cap.open(0,cv::CAP_MSMF);
	if (cap.isOpened()) {
		log.info("Camera opened at index: " + std::to_string(index));

		startTime = std::chrono::high_resolution_clock::now();
		
		double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
		double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		double camFps = cap.get(cv::CAP_PROP_FPS);

		log.info("Camera resolution: " + std::to_string((int)width) + "x" + std::to_string((int)height));
		log.info("Camera reported FPS: " + std::to_string(camFps));
		return true;
	}
	else {
		log.error("Failed to open camera at index: " + std::to_string(index));
		return false;
	}
	
}

void CameraSource::closeCamera()
{
	cap.release();
}

bool CameraSource::isCameraOpen()
{
	return cap.isOpened();
}

cv::Mat CameraSource::captureFrame()
{
	cv::Mat frame;

	if (!cap.isOpened()) 
	{
		log.warning("Camera is not open.");
		return frame;
	}
		bool ok = cap.read(frame);
		
		if(!ok || frame.empty()) {
			emptyFrameCount++;
			if (emptyFrameCount > 100) {
				log.error("Too many empty frames captured. Stopping capture.");
				closeCamera();
			}
			return cv::Mat();
		}

		emptyFrameCount = 0; // Reset empty frame count on successful capture

			auto now = std::chrono::high_resolution_clock::now();

			frameCount++;
			std::chrono::duration<double> elapsed = now - startTime;
			if (elapsed.count() >= 1.0) {
				fps = frameCount / elapsed.count();
				frameCount = 0;
				startTime = now;
				log.info("FPS: " + std::to_string(fps));
			}

			cv::putText(
				frame,
				"FPS: " + std::to_string(static_cast<int>(fps)),
				cv::Point(10, 30),
				cv::FONT_HERSHEY_SIMPLEX,
				1.0,
				cv::Scalar(0, 255, 0),
				2
			);
	
	
	return frame;
}
