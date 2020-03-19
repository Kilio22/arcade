/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** InvalidLibraryException
*/

#include "Exceptions/InvalidLibraryException.hpp"

Arcade::Exceptions::InvalidLibraryException::InvalidLibraryException(std::string const &message, std::string const &component)
    : ArcadeException(message, component)
{
}
