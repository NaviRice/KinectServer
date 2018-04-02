CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(NAVIRICE_CPP)

SET(CMAKE_CXX_STANDARD 11)
SET(SOURCE
	src/navirice_image_distribution_server.cc
	src/navirice_image_impl.cc
)

# Threads
FIND_PACKAGE(Threads REQUIRED)

# Protobuf
ADD_SUBDIRECTORY(proto)

# FREENECT2 for kinect
find_package(freenect2 REQUIRED)
message(STATUS "freenect2_LIBRARIES: " ${freenect2_LIBRARIES})
message(STATUS "freenect2_INCLUDE_DIR: " ${freenect2_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#proto_lib is taken from proto directory
ADD_EXECUTABLE(test_program test_program.cc ${SOURCE})
TARGET_LINK_LIBRARIES(test_program ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(test_program proto_lib)

ADD_EXECUTABLE(kinect_server kinect_server.cc ${SOURCE})
TARGET_LINK_LIBRARIES(kinect_server ${CMAKE_THREAD_LIBS_INIT})
TARGET_INCLUDE_DIRECTORIES(kinect_server PUBLIC ${freenect2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(kinect_server ${freenect2_LIBRARIES})
TARGET_LINK_LIBRARIES(kinect_server proto_lib)


