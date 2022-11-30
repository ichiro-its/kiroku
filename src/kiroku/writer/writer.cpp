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

#include "kiroku/writer/writer.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using nlohmann::json;

json json_log = {};

std::unordered_map<std::string, int> string_to_log_level 
{
  {"DEBUG", 0},
  {"INFO", 1},
  {"WARN", 2},
  {"ERROR", 3},
  {"FATAL", 4},
};

Writer::Writer()
{
}

void Writer::write_to_file(
  const std::string &filename, const std::string &message_logger, const std::string &level, const std::string &time)
{
  logger_level = string_to_log_level[level];

  if (logger_level >= filter_level) {
    std::ofstream file_logger;
    file_logger.open(
      "src/kiroku/" + filename + ".log",
      std::ios_base::trunc | std::ios_base::out);

    json_log += {
      {"message_log", message_logger},
      {"level", level},
      {"time", time}
    };

    file_logger << json_log.dump();

    file_logger.close();
  }
}
