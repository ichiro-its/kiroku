#ifndef KIROKU__LOGGER_SUB_NODE_HPP_
#define KIROKU__LOGGER_SUB_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"

class LoggerSub : public rclcpp::Node
{
public:
  LoggerSub();

private:
  void topic_callback(const first_interfaces::msg::Log::SharedPtr msg) const;

  rclcpp::Subscription<first_interfaces::msg::Log>::SharedPtr subscription_;
};
#endif
