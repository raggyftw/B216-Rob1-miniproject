# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 2.8)

# Declare the name of the CMake Project
project(pianobot)



# Find Catkin
find_package(catkin REQUIRED
  roscpp
  rospy
  std_msgs
  sensor_msgs 
  cv_bridge
  image_transport
  )
find_package(Boost REQUIRED)
# Declare this project as a catkin package
catkin_package()

# Add the local headers and the headers from roscpp
include_directories(include	
	${catkin_INCLUDE_DIRS}		    
)


# Define the executables used in guidebot.
add_executable(detection_node src/detection_node.cpp)
add_executable(subscriber_node src/subscriber_node.cpp)
 
# link libraries of the target files. 
target_link_libraries(detection_node ${catkin_LIBRARIES})
target_link_libraries(subscriber_node ${catkin_LIBRARIES}) 
