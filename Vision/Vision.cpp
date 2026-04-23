// Vision.cpp : Defines the entry point for the application.
//

#include "Vision.h"
#include "vision/logger.h"
#include "src/device/CameraProbe.h"
#include "src/device/CameraSource.h"
#include <cstdlib>

using namespace std;

int main()
{
	Logger log = Logger();
	/*cout << "Hello CMake." << endl;
	log.info("This is an info message [INFO] - need to be blue");
	log.error("This is an error message. [ERROR] - need to be red color");
	log.warning("This is an warning message. [WARNING] = need to be Yellow color");
	*/
	
	/*CameraProbe probe(log);
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

	while (true) {
		cv::Mat frame = camera.captureFrame();

		if (frame.empty()) {
			if(!camera.isCameraOpen()) {
				break;
			}
			continue; 
		}

		cv::imshow("Camera", frame);

		if (cv::waitKey(1) >= 0)
			break;
	}

	camera.closeCamera();*/




    cv::VideoCapture cap;

    // Список API для перебора: 
    // DSHOW (DirectShow) - самый стабильный для Windows
    // MSMF - современный стандарт Windows
    // ANY - автоматический выбор
    std::vector<int> apis = { cv::CAP_DSHOW, cv::CAP_MSMF, cv::CAP_ANY };

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

    return 0;
}
