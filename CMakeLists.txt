cmake_minimum_required(VERSION 2.8.3)
project(pgs_device_driver)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  serial
)

add_service_files(
   FILES
   PGSCmd.srv
)

add_message_files(
   FILES
   ethanolsensor.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
   src/PGSDeviceDriver.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
)

add_executable(${PROJECT_NAME}_node src/pgs_device_driver_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME}
   ${catkin_LIBRARIES}
)
