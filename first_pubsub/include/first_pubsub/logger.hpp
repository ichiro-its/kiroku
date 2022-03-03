#ifndef FIRST_PUBSUB__LOGGER_HPP_
#define FIRST_PUBSUB__LOGGER_HPP_

#include "first_interfaces/msg/log.hpp"

class Logger
{
    public:
        Logger();
        void write_logger(const first_interfaces::msg::Log::SharedPtr msg) const;

};
#endif