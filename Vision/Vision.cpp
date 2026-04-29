// Vision.cpp : Defines the entry point for the application.
//

#include "Vision.h"
#include "vision/logger.h"
#include "vision/YoloDetector.h"
#include "vision/AppState.h"
#include "vision/ConsoleMenu.h"
#include "src/device/CameraProbe.h"
#include "src/device/CameraSource.h"
#include <cstdlib>
#include<thread> 
#include <mutex>
#include <atomic>

using namespace std;

int main()
{
    vision::AppState state;
    std::thread menuThread(vision::runConsoleMenu, std::ref(state));

    menuThread.join();

    Logger log = Logger();

    YoloDetector yolo = YoloDetector();
    CameraProbe probe(log);
	vector<int> cameras = probe.probeCameras();
	if (cameras.empty()) {
		log.error("No cameras found.");
		return -1;
	}

	CameraSource camera(log);
	if (!camera.openCamera(cameras[0])) {
		log.error("Failed to open camera.");
		return -1;
	}
    int frameId = 0;
    std::vector<Detection> lastDetection;

    std::mutex frameMutex;
    std::mutex detectionMutex;

    cv::Mat latestFrameForDetection;
    
    std::atomic<bool> running = true;
    std::atomic<bool> hasNewFrame = false;

    std::thread detectorThread([&]() {
        while (running) {
            cv::Mat frameCopy;
            {
                std::lock_guard<std::mutex> lock(frameMutex);

                if (!hasNewFrame || latestFrameForDetection.empty()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }
                latestFrameForDetection.copyTo(frameCopy);
                hasNewFrame = false;
            }

            auto detections = yolo.detect(frameCopy);
            {            
                std::lock_guard<std::mutex>lock(detectionMutex);
                if (!detections.empty()) {
                    lastDetection = detections;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        });
    while (true) {
		cv::Mat frame = camera.captureFrame();

		if (frame.empty()) {
			if(!camera.isCameraOpen()) {
				break;
			}
			continue; 
		}
        {
            std::lock_guard<std::mutex>lock(frameMutex);
            frame.copyTo(latestFrameForDetection);
            hasNewFrame = true;
        }
       

        std::vector<Detection> detectionsToDraw;
        {
            std::lock_guard<std::mutex> lock(detectionMutex);
            detectionsToDraw = lastDetection;
        }
        for (const Detection& det : detectionsToDraw) {
            cv::rectangle(frame, det.box, cv::Scalar(0, 255, 0), 2);
            
            cv::Point textPos(det.box.x, std::max(20, det.box.y - 10));

            cv::putText(
            frame,
                det.className + " " + std::to_string((int)(det.confidence * 100)) + "%",
                textPos,
                cv::FONT_HERSHEY_SIMPLEX,
                0.5,
                cv::Scalar(0,255,0),
                2
            );
        }

        frameId++;
        cv::imshow("Camera", frame);

		if (cv::waitKey(1) >= 0)
			break;
	}
    running = false;
    if (detectorThread.joinable()) {
        detectorThread.join();
    }
	camera.closeCamera();

    /*


    cv::VideoCapture cap;

    // Список API для перебора: 
    // DSHOW (DirectShow) - самый стабильный для Windows
    // MSMF - современный стандарт Windows
    // ANY - автоматический выбор

    bool found = false;

    std::cout << "Searching for camera..." << std::endl;

    for (int api : apis) {
        for (int i = 0; i < 3; i++) { // Проверяем индексы 0, 1, 2
            cap.open(i, api);
            if (cap.isOpened()) {
                std::cout << "SUCCESS: Found camera on index " << i
                    << " with API " << api << std::endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        std::cerr << "ERROR: No camera found. Check Privacy Settings or connection." << std::endl;
        return -1;
    }

    // Настройки для стабильности
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (true) {
        cv::Mat frame;
        if (!cap.read(frame) || frame.empty()) {
            // Если один кадр не прочитался, не вылетаем, а пробуем снова
            cv::waitKey(10);
            continue;
        }

        cv::imshow("Camera Test", frame);

        if (cv::waitKey(1) >= 0) break;
    }

    return 0;*/
}
