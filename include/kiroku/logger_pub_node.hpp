#ifndef KIROKU__LOGGER_PUB_NODE_HPP_
#define KIROKU__LOGGER_PUB_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"     // CHANGE

class LoggerPub : public rclcpp::Node
{
public:
  LoggerPub();

private:
  void topic_callback();

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<first_interfaces::msg::Log>::SharedPtr publisher_;         // CHANGE
  size_t count_;
};
#endif
