# CMakeList.txt : CMake project for Vision, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Vision "Vision.cpp" 
"Vision.h" 
 
"src/core/logger.cpp" 
"include/vision/logger.h"
 "src/device/CameraProbe.h"
 "src/device/CameraProbe.cpp"
 "src/core/ConsoleMenu.cpp"
  "src/device/CameraSource.h" "src/device/CameraSource.cpp" "include/vision/YoloDetector.h" "src/vision/YoloDetector.cpp" "include/vision/IDetector.h")
target_include_directories(Vision PRIVATE include)

find_package(OpenCV REQUIRED)

target_link_libraries(Vision PRIVATE ${OpenCV_LIBS})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Vision PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
