## ROS2 abstraction interface demo

This is an example of ROS2 publisher and subscriber abstraction interfaces, demonstrating how to isolate application logic from ROS2 calls.

### Build:

- `colcon build --packages-select ros2_abstraction_demo`
- `source install/setup.bash`

### Run sender:
- `ros2 run ros2_abstraction_demo sender_ros_app`

### Run receiver:
- `ros2 run ros2_abstraction_demo receiver_ros_app`