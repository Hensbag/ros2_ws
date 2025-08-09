from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    launch = os.path.join(
        get_package_share_directory('smart_can_stuff'),
        'launch',
        'pid_params.yaml'
    )

    return LaunchDescription([
        Node(
            package='smart_can_stuff',
            executable='steering_pid_node',
            name='steering_pid_node',
            output='screen',
            parameters=[launch]
        ),

        Node(
            package='smart_can_stuff',
            executable='speed_pid_node',
            name='speed_pid_node',
            output='screen',
            parameters=[launch]
        )
    ])
