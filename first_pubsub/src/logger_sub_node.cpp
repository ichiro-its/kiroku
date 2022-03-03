#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using std::placeholders::_1;
#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"
// #include "first_pubsub/logger.hpp"
#include "first_pubsub/logger_sub_node.hpp"

using json = nlohmann::json;
using std::placeholders::_1;


    LoggerSub::LoggerSub()
    : Node("logger_sub")
    {
        subscription_ = this->create_subscription<first_interfaces::msg::Log>(
            "topic", 10, std::bind(&LoggerSub::topic_callback, this, _1)
        );

        // logger = Logger();
        // logger.write_logger(msg);
    }


    void LoggerSub::topic_callback(const first_interfaces::msg::Log::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "filename: '%s'\nmessage log: '%s'\nlevel: '%s'\ntime: '%s'",
        msg->filename, msg->message_log, msg->level, msg->time);

            std::ofstream file_log;
            file_log.open("logger.json", std::ios_base::trunc | std::ios_base::out);

            json json_log = json::array();

            for(int i = 0; i < 10; i++){

                json jsn_lg = {
                    //{"", this->get_logger()},
                    {"message_log", msg->message_log},
                    {"level", msg->level},
                    {"time", msg->time}
                };
                json_log.push_back(jsn_lg);
            }

            file_log << json_log.dump(0);

            file_log.close();
    }
