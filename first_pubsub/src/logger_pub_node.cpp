#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"
#include "first_pubsub/logger_pub_node.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

  LoggerPub::LoggerPub()
  : Node("logger_pub")
  {
    publisher_ = this->create_publisher<first_interfaces::msg::Log>("topic", 10);
    timer_ = this->create_wall_timer(500ms, std::bind(&LoggerPub::topic_callback, this));
  }

  void LoggerPub::topic_callback() 
  {
    auto message = first_interfaces::msg::Log();
    message.filename = "anaz";
    message.message_log = "ppp";
    message.level = "INfo";
    message.time = "500";
    publisher_->publish(message);
  }
