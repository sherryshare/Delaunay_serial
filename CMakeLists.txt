PROJECT(DELAUNAY)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
MESSAGE(STATUS "This is BINARY dir" ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir" ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)
#add_definitions(-DUSING_LOCK_FREE_QUEUE)
add_definitions(-DUSING_FF_SPIN_STEAL_QUEUE)

message(STATUS "Building Delaunay")
SET(DELAUNAY_LIST main.cpp
		spatial_sort.cpp
		doubly_linked_listnode.cpp)

find_package(GLUT)
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})		
ADD_EXECUTABLE(delaunay ${DELAUNAY_LIST})
TARGET_LINK_LIBRARIES(delaunay ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


