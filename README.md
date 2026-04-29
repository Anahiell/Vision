# Vision

Vision is a c++ computer vision sandbox project build with OpenCv.
The goal of the project is to experiment with camera input, device probing, YOLO-based object detection, logging, and a simple console control menu(for now).

## Current Futures

- Camera probing and camera source abstraction
- OpenCv-based video Capture
- YOLO detector integration
- Drawing detection boxes on live camera frame
- Console menu thread for basic runtime control(on work)
- Simple custom logger(+-)
- CMake-based project structure


## Tech Stack

  - C++20
  - Cmake
  - OpenCv
  - YOLOv3
  - need GPU(maybe CUDA or DirectX)

    
## Project Structure

  ```txt
    Vision/
    ├── include/vision/        # Public headers
    ├── src/core/              # Logger and console menu logic
    ├── src/device/            # Camera probing and camera source
    ├── src/vision/            # YOLO detector logic
    ├── models/                # Local model files, not pushed to Git
    ├── Vision.cpp             # Entry point
    └── CMakeLists.txt
```

## Requirements

- Visual Studio 2022
- CMake
- OpenCV
- C++20 compatible compiler


## Configure and build with CMake:

```cmake
    set(OpenCV_DIR "D:/cppLib/opencv/build")
    find_package(OpenCV REQUIRED)
    target_link_libraries(Vision PRIVATE ${OpenCV_LIBS})
```

## Expected local structure:
```txt
Vision/models/yolo/
├── coco.names
├── yolov3.cfg
└── yolov3.weights
```

## Planned Improvements:
- Improve YOLO detection performance
- Add better runtime menu controls
- Add configuration files for model paths and camera settings
- Add better error handling
- Add cleaner threading and shutdown logic
- Add GPU acceleration experiments
