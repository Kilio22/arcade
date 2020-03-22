/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

namespace Arcade
{
    class Logger
    {
        public:
            enum LogLevel
            {
                ERROR,
                DEBUG
            };

        private:
            Logger() = default;
        public:
            Logger(const Logger &) = delete;
            ~Logger() = default;

            void operator=(const Logger &) = delete;

            static void log(const std::string &message, LogLevel level);
            static void log(std::ostringstream message, LogLevel level);
            static void setLogLevel(LogLevel level);

        private:
            static LogLevel level;
    };
}

#endif /* !LOGGER_HPP_ */
