## ROS2 abstraction interface demo

This is an example of ROS2 publisher and subscriber abstraction interfaces, demonstrating how to isolate application logic from ROS2 calls.
All code is concept demonstration and not for production.

### Build:

- `colcon build --packages-select ros2_abstraction_demo`
- `source install/setup.bash`

### Run ROS2 sender:
- `ros2 run ros2_abstraction_demo sender_ros_app`

### Run ROS2 receiver:
- `ros2 run ros2_abstraction_demo receiver_ros_app`

### Run Sockets sender:
- `ros2 run ros2_abstraction_demo sender_socket_app`

### Run Sockets receiver:
- `ros2 run ros2_abstraction_demo receiver_socket_app`