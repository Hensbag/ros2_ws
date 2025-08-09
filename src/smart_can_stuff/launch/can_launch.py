
from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.substitutions import ThisLaunchFileDir
from launch_ros.actions import Node


def generate_launch_description():
    # params_file = LaunchConfiguration(
    #     'params',
    #     default=[ThisLaunchFileDir(), '/launch_params.yaml'])

    # make sure the dbc file gets installed with the launch file
    dbc_file_path = get_package_share_directory('smart_can_stuff') + \
        '/launch/disv3signed.dbc'

    return LaunchDescription(
        [
            Node(
                package='smart_can_stuff',
                executable='can2ros_node',
                output='screen',
                namespace='smart_can_stuff_interface',
                parameters=[
                    {'dbw_dbc_file': dbc_file_path}
                ],
            ),
        ])


generate_launch_description()
