cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(LearningOpenCV3)

find_package( OpenCV REQUIRED )
find_package( OpenGL )

if(OPENGL_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} )
else()
  include_directories( ${OpenCV_INCLUDE_DIRS} )
endif()

add_executable( 2-1 ch02/1.display.cpp )
add_executable( 2-3 ch02/3.video.cpp )
add_executable( 2-4 ch02/4.trackbar.cpp )
add_executable( 2-5 ch02/5.smoothing.cpp )
 
target_link_libraries( 2-1 ${OpenCV_LIBS} )
target_link_libraries( 2-3 ${OpenCV_LIBS} )
target_link_libraries( 2-4 ${OpenCV_LIBS} )
target_link_libraries( 2-5 ${OpenCV_LIBS} )
