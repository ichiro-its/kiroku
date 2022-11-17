// Copyright (c) 2022 Ichiro ITS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "kiroku/node/kiroku_node.hpp"
#include <string.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "rclcpp/rclcpp.hpp"
#include "kiroku/writer/writer.hpp"
#include "kiroku_interfaces/msg/logger.hpp"

using json = nlohmann::json;
using std::placeholders::_1;

enum LoggerLevel
{
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL
};
json json_log = {};

KirokuNode::KirokuNode()
: Node("kiroku_node")
{
  subscription_ = this->create_subscription<kiroku_interfaces::msg::Logger>(
    "topic", 10,
    [this](const kiroku_interfaces::msg::Logger::SharedPtr msg) {
      RCLCPP_INFO(
        this->get_logger(), "filename: '%s'\nmessage log: '%s'\nlevel: '%s'\ntime: '%s'",
        msg->filename, msg->message_logger, msg->level, msg->time);

      int logger_level = 0;
      if (msg->level.compare("DEBUG") == 0) {
        logger_level = 0;
      } else if (msg->level.compare("INFO") == 0) {
        logger_level = 1;
      } else if (msg->level.compare("WARN") == 0) {
        logger_level = 2;
      } else if (msg->level.compare("ERROR") == 0) {
        logger_level = 3;
      } else if (msg->level.compare("FATAL") == 0) {
        logger_level = 4;
      }

      LoggerLevel filter_level = INFO;

      if (logger_level >= filter_level) {
        std::ofstream file_logger;
        file_logger.open(
          "src/kiroku/" + msg->filename + ".log",
          std::ios_base::trunc | std::ios_base::out);

        json_log += {
          {"message_log", msg->message_logger},
          {"level", msg->level},
          {"time", msg->time}
        };

        file_logger << json_log.dump();

        file_logger.close();
      }
    }
  );
}
