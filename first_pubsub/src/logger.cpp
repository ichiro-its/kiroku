

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

#include "first_interfaces/msg/log.hpp"
#include "first_pubsub/logger.hpp"


using std::placeholders::_1;
using json = nlohmann::json;



        Logger::Logger(){}
        void Logger::write_logger(const first_interfaces::msg::Log::SharedPtr msg) const
        {
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

