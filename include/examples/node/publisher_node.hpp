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

#ifndef EXAMPLES__NODE__PUBLISHER_NODE_HPP_
#define EXAMPLES__NODE__PUBLISHER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "kiroku_interfaces/msg/logger.hpp"

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode();

private:
  void topic_callback();

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<kiroku_interfaces::msg::Logger>::SharedPtr publisher_;
  size_t count_;
};
#endif  // EXAMPLES__NODE__PUBLISHER_NODE_HPP_
