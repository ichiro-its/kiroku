#ifndef FIRST_PUBSUB__LOGGER_SUB_NODE_HPP_
#define FIRST_PUBSUB__LOGGER_SUB_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"
// #include "first_pubsub/logger.hpp"

class LoggerSub : public rclcpp::Node
{
public:
    LoggerSub();

private:
    // void filter_log(const first_interfaces::msg::Log::SharedPtr msg) const;

    void topic_callback(const first_interfaces::msg::Log::SharedPtr msg) const;

    rclcpp::Subscription<first_interfaces::msg::Log>::SharedPtr subscription_;
};
#endif