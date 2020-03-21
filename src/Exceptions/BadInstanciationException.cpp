/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** BadInstanciationException
*/

#include "Exceptions/BadInstanciationException.hpp"

Arcade::Exceptions::BadInstanciationException::BadInstanciationException(std::string const &message, std::string const &component)
    : ArcadeException(message, component)
{}