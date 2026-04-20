# CMakeList.txt : CMake project for Vision, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Vision "Vision.cpp" 
"Vision.h" 
 
"src/core/logger.cpp" 
"include/vision/logger.h"
)
target_include_directories(Vision PRIVATE include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Vision PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
