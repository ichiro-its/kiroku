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
#include "kiroku_interfaces/msg/logger.hpp"

using std::placeholders::_1;

KirokuNode::KirokuNode()
: Node("kiroku_node")
{
  subscription_ = this->create_subscription<kiroku_interfaces::msg::Logger>(
    "topic", 10,
    [this](const kiroku_interfaces::msg::Logger::SharedPtr msg) {
      RCLCPP_INFO(
        this->get_logger(), "filename: '%s'\nmessage log: '%s'\nlevel: '%s'\ntime: '%s'",
        msg->filename, msg->message_logger, msg->level, msg->time);

      write.write_to_file(msg->filename, msg->message_logger, msg->level, msg->time);
    }
  );
}
