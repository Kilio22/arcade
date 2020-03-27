/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <iostream>

namespace Arcade
{
    /**
     * @brief Used to display error messages depending on the set log level.
     */
    class Logger
    {
        public:
            /**
             * @brief Available log levels.
             */
            enum LogLevel
            {
                ERROR, ///< Displays unexpected errors */
                DEBUG  ///< Used for debugging */
            };

        private:
            Logger() = default;
        public:
            Logger(const Logger &) = delete;
            ~Logger() = default;

            void operator=(const Logger &) = delete;

            /**
             * @brief Logs the given message to the output
             * @param level The log level of the message
             * @param args Every argument are going to be assembled using std::cerr << ... << args
             */
            template <typename ... Args>
            static void log(LogLevel level, Args &&...args)
            {
                if (level <= Logger::level)
                    (std::cerr << ... << args) << std::endl;
            }

            /**
             * @brief Sets the current log level.
             * @param level Log level value.
             */
            static void setLogLevel(LogLevel level);

        private:
            static LogLevel level;
    };
}

#endif /* !LOGGER_HPP_ */
