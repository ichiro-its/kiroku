#ifndef FIRST_PUBSUB__LOGGER_PUB_NODE_HPP_
#define FIRST_PUBSUB__LOGGER_PUB_NODE_HPP_

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

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

/*
class LoggerPub : public rclcpp::Node
{
public:
  LoggerPub();

private:
  void topic_callback(const first_interfaces::msg::Log::SharedPtr msg) const;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<first_interfaces::msg::Log>::SharedPtr publisher_;
  //size_t count_;
};
*/
#endif
