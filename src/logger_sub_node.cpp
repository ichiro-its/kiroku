#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <nlohmann/json.hpp>

using std::placeholders::_1;
#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/log.hpp"
#include "kiroku/logger_sub_node.hpp"

using json = nlohmann::json;
using std::placeholders::_1;

enum LogLevel { DEBUG, INFO, WARN, ERROR, FATAL };
json jsn_lg = {};

LoggerSub::LoggerSub()
: Node("logger_sub")
{
  subscription_ = this->create_subscription<kiroku_interfaces::msg::Log>(
    "topic", 10, std::bind(&LoggerSub::topic_callback, this, _1)
  );

}

void LoggerSub::topic_callback(const kiroku_interfaces::msg::Log::SharedPtr msg) const
{
  RCLCPP_INFO(
    this->get_logger(), "filename: '%s'\nmessage log: '%s'\nlevel: '%s'\ntime: '%s'",
    msg->filename, msg->message_log, msg->level, msg->time);

  int log_level;
  if (msg->level.compare("DEBUG") == 0) {
    log_level = 0;
  } else if (msg->level.compare("INFO") == 0) {
    log_level = 1;
  } else if (msg->level.compare("WARN") == 0) {
    log_level = 2;
  } else if (msg->level.compare("ERROR") == 0) {
    log_level = 3;
  } else if (msg->level.compare("FATAL") == 0) {
    log_level = 4;
  }

  LogLevel filter_level = INFO;

  if (log_level >= filter_level) {
    std::ofstream file_log;
    file_log.open(
      "src/kiroku/" + msg->filename + ".log",
      std::ios_base::trunc | std::ios_base::out);

    jsn_lg += {
      {"message_log", msg->message_log},
      {"level", msg->level},
      {"time", msg->time}
    };

    file_log << jsn_lg.dump();

    file_log.close();

  }

}
