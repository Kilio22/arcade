/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Logger
*/

#include <iostream>
#include "Logger.hpp"

Arcade::Logger::LogLevel Arcade::Logger::level = ERROR;

void Arcade::Logger::setLogLevel(LogLevel level)
{
    Logger::level = level;
}
