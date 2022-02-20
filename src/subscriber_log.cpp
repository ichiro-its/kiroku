#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "kiroku/msg/log.hpp"

using namespace std::chrono_literals;

class LogSubscriber : public rclcpp::Node
{
    public:
    LogSubscriber()
    : Node("log_subscriber")
    {
        log_subscriber = this->create_subscription<kiroku::msg::log>(
            "topic", 10, std::bind(&log_subscriber::topic_callback, this, _1)
        );
    }

    private:
    void topic_callback(const kiroku::msg::log::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), msg->log);
    }
    rclcpp::Subscription<kiroku::msg::log>::SharedPtr subscription_;
}:

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<log_subscriber>());
    rclcpp::shutdown();

    return 0;
}
