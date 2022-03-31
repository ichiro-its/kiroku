#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <nlohmann/json.hpp>

using std::placeholders::_1;
#include "rclcpp/rclcpp.hpp"
#include "first_interfaces/msg/log.hpp"
// #include "first_pubsub/logger.hpp"
#include "first_pubsub/logger_sub_node.hpp"

using json = nlohmann::json;
using std::placeholders::_1;

enum LogLevel { DEBUG, INFO, WARN, ERROR, FATAL };
// int array_available = 0;
json jsn_lg = {};

    LoggerSub::LoggerSub()
    : Node("logger_sub")
    {
        subscription_ = this->create_subscription<first_interfaces::msg::Log>(
            "topic", 10, std::bind(&LoggerSub::topic_callback, this, _1)
        );

    }


    void LoggerSub::topic_callback(const first_interfaces::msg::Log::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "filename: '%s'\nmessage log: '%s'\nlevel: '%s'\ntime: '%s'",
        msg->filename, msg->message_log, msg->level, msg->time);

        enum LogLevel log_level;
        log_level = INFO;
        int filter_level = 0;

        if(log_level >= filter_level)
        {
            std::ofstream file_log;
            file_log.open("src/first_pubsub/" + msg->filename + ".log", std::ios_base::trunc | std::ios_base::out);

            
            // if(!array_available) {
            //     json_log = json::array();
            //     array_available = 1;
            // }

            jsn_lg += {
                {"message_log", msg->message_log},
                {"level", msg->level},
                {"time", msg->time}
            };

            // json_log += jsn_lg;

            file_log << jsn_lg.dump(0);

            file_log.close();

        }

    }

