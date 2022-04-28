#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/log.hpp"
#include "kiroku/logger_pub_node.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

LoggerPub::LoggerPub()
: Node("logger_pub")
{
  publisher_ = this->create_publisher<kiroku_interfaces::msg::Log>("topic", 10);
  timer_ = this->create_wall_timer(500ms, std::bind(&LoggerPub::topic_callback, this));
}

void LoggerPub::topic_callback()
{
  auto message = kiroku_interfaces::msg::Log();
  message.filename = "logger";
  message.message_log = "ini message";
  message.level = "INFO";
  message.time = "1000";
  publisher_->publish(message);
}
