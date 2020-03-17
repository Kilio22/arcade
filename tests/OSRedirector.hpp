/*
** EPITECH PROJECT, 2020
** cpp_d06_2019
** File description:
** OSRedirector
*/

#ifndef OSREDIRECTOR_HPP_
#define OSREDIRECTOR_HPP_

#include <ostream>
#include <iostream>
#include <criterion/criterion.h>

class OSRedirector {
    private:
        std::ostringstream _oss;
        std::streambuf *_backup;
        std::ostream &_c;

    public:
        OSRedirector(std::ostream &c) : _c(c) {
            _backup = _c.rdbuf();
            _c.rdbuf(_oss.rdbuf());
        }

        ~OSRedirector() {
            _c.rdbuf(_backup);
        }

        const std::string getContent() {
            _oss << std::flush;
            return _oss.str();
        }
};

#endif /* !OSREDIRECTOR_HPP_ */
