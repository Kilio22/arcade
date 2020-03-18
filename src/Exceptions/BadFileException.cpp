/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** BadFileException
*/

#include "Exceptions/BadFileException.hpp"

Arcade::Exceptions::BadFileException::BadFileException(std::string const &message, std::string const &component)
    : ArcadeException(message, component)
{
}
