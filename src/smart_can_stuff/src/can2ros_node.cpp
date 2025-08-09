
#include "smart_can_stuff/can2ros.hpp"
#include <memory>
#include <string>


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options{};
  rclcpp::executors::SingleThreadedExecutor exec{};


  // Get parameter values
  auto temp = std::make_shared<rclcpp::Node>("get_dbw_params_node", options);
  temp->declare_parameter<std::string>("dbw_dbc_file");

  std::string n_dbw_dbc_file = temp->get_parameter("dbw_dbc_file").as_string();

  // Create CanListener class
  auto node = std::make_shared<smart_can_stuff::CanListener>(
    options,
    n_dbw_dbc_file
  );
  
  exec.add_node(node->get_node_base_interface());
  exec.spin();

  rclcpp::shutdown();

  return 0;
}
