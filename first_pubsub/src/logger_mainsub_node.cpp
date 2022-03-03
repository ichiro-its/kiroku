

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"
#include "first_pubsub/logger.hpp"
#include "first_pubsub/logger_sub_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LoggerSub>());
    rclcpp::shutdown();

    return 0;
}
