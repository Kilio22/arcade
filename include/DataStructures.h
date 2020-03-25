/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DataStructures
*/

#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include "lib/IDisplayModule.hpp"

struct rectangle_s {
    float x;
    float y;
    float w;
    float h;
    Arcade::Display::IDisplayModule::Colors color;
};
typedef struct rectangle_s rectangle_t;

struct circle_s {
    float x;
    float y;
    float radius;
    Arcade::Display::IDisplayModule::IDisplayModule::Colors color;
};
typedef struct circle_s circle_t;

struct pixel_s {
    float x;
    float y;
    Arcade::Display::IDisplayModule::IDisplayModule::Colors color;
};
typedef struct pixel_s pixel_t;

struct line_s {
    float x1;
    float y1;
    float x2;
    float y2;
    Arcade::Display::IDisplayModule::IDisplayModule::Colors color;
};
typedef struct line_s line_t;

#endif /* !DATASTRUCTURES_H_ */
