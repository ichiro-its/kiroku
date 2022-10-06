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

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/logger.hpp"
#include "kiroku/logger_publisher.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

LoggerPublisher::LoggerPublisher()
: Node("logger_publisher")
{
  publisher_ = this->create_publisher<kiroku_interfaces::msg::Logger>("topic", 10);
  timer_ = this->create_wall_timer(500ms, std::bind(&LoggerPublisher::topic_callback, this));
}

void LoggerPublisher::topic_callback()
{
  auto message = kiroku_interfaces::msg::Logger();
  message.filename = "logger";
  message.message_logger = "this message";
  message.level = "INFO";
  message.time = "1000";
  publisher_->publish(message);
}
