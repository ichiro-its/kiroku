#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/log.hpp"
#include "kiroku/logger_pub_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LoggerPub>());
  rclcpp::shutdown();

  return 0;
}
