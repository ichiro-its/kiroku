#ifndef KIROKU__LOGGER_PUB_NODE_HPP_
#define KIROKU__LOGGER_PUB_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/log.hpp"     // CHANGE

class LoggerPub : public rclcpp::Node
{
public:
  LoggerPub();

private:
  void topic_callback();

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<kiroku_interfaces::msg::Log>::SharedPtr publisher_;         // CHANGE
  size_t count_;
};
#endif
