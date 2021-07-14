cmake_minimum_required(VERSION 3.8)
project(ros2_abstraction_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ROS version
add_executable(sender_ros_app
  src/apps/sender_app.cpp
  src/ros2/factory_ros2.cpp
)
ament_target_dependencies(sender_ros_app rclcpp std_msgs)

add_executable(receiver_ros_app
  src/apps/receiver_app.cpp
  src/ros2/factory_ros2.cpp
)
ament_target_dependencies(receiver_ros_app rclcpp std_msgs)

# Socket version
add_executable(sender_socket_app
  src/apps/sender_app.cpp
  src/socket/factory_socket.cpp
)
target_link_libraries(sender_socket_app -lpthread)

add_executable(receiver_socket_app
  src/apps/receiver_app.cpp
  src/socket/factory_socket.cpp
)
target_link_libraries(receiver_socket_app -lpthread)

install(TARGETS
  sender_ros_app
  receiver_ros_app
  sender_socket_app
  receiver_socket_app
  DESTINATION lib/${PROJECT_NAME})

ament_package()
