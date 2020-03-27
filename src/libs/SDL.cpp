/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#include <functional>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "lib/SDL.hpp"
#include "Exceptions/BadInstanciationException.hpp"
#include "Exceptions/BadFileException.hpp"

const std::vector<SDL_Color> Arcade::Display::SDL::_libColors =
{
    {0, 0, 0, 255},
    {0, 0, 0, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {255, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 0, 255, 255},
    {0, 255, 255, 255},
    {128, 128, 128, 255},
    {105, 105, 105, 255},
    {240, 128, 128, 255},
    {0, 255, 111, 255},
    {255, 255, 64, 255},
    {0, 162, 255, 255},
    {255, 0, 247, 255},
    {0, 247, 255, 255},
    {255, 255, 255, 255}
};

const std::vector<SDL_Keycode> Arcade::Display::SDL::_libKeys =
{
    SDLK_LEFT,
    SDLK_RIGHT,
    SDLK_UP,
    SDLK_DOWN,
    SDLK_z,
    SDLK_q,
    SDLK_s,
    SDLK_d,
    SDLK_a,
    SDLK_e,
    SDLK_w,
    SDLK_x,
    SDLK_SPACE,
    SDLK_j,
    SDLK_k,
    SDLK_u,
    SDLK_i,
    SDLK_RETURN,
    SDLK_ESCAPE,
    SDLK_m,
    SDLK_r,
};

extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<Arcade::Display::SDL>();
}

Arcade::Display::SDL::SDL()
    : ADisplayModule("SDL"),
    _window(nullptr), _currentColor(Colors::DEFAULT), _events(SystemKeys::SYSKEYS_END, false), _keyCode('\0')
{
}

Arcade::Display::SDL::~SDL()
{
    if (this->_window != nullptr) {
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);
        TTF_Quit();
        SDL_Quit();
    }
}

void Arcade::Display::SDL::reset()
{}

void Arcade::Display::SDL::open()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        throw Arcade::Exceptions::BadInstanciationException(std::string("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError())), "SDL::open");
    }
    this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FULL_WIDTH, FULL_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->_window == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Window creation failed.", "SDL::open");
    }
    this->_surface = SDL_GetWindowSurface(this->_window);
    if (this->_surface == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Surface creation failed.", "SDL::open");
    }
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == nullptr) {
        throw Arcade::Exceptions::BadInstanciationException("Renderer creation failed.", "SDL::open");
    }
    SDL_StartTextInput();
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255); // set to current color
    this->_fonts = std::make_unique<std::map<unsigned int, TTF_Font *>>();
}

bool Arcade::Display::SDL::isOpen() const
{
    return true;
}

bool Arcade::Display::SDL::switchToNextLib() const
{
    return this->_events.at(Keys::RIGHT);
}

bool Arcade::Display::SDL::switchToPreviousLib() const
{
    return this->_events.at(Keys::LEFT);
}

bool Arcade::Display::SDL::switchToNextGame() const
{
    return this->_events.at(Keys::UP);
}

bool Arcade::Display::SDL::switchToPreviousGame() const
{
    return this->_events.at(Keys::DOWN);
}

bool Arcade::Display::SDL::shouldBeRestarted() const
{
    return this->_events.at(SystemKeys::R);
}

bool Arcade::Display::SDL::shouldGoToMenu() const
{
    return this->_events.at(SystemKeys::M);
}

bool Arcade::Display::SDL::shouldExit() const
{
    return this->_events.at(SystemKeys::ESCAPE);
}

bool Arcade::Display::SDL::isKeyPressed(IDisplayModule::Keys key) const
{
    auto keyboard = SDL_GetKeyboardState(NULL);

    return keyboard[SDL_GetScancodeFromKey(this->_libKeys.at(key))];
}

bool Arcade::Display::SDL::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return this->_events.at(key);
}

float Arcade::Display::SDL::getDelta() const
{
    return 1;
}

void Arcade::Display::SDL::clear() const
{
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255); // set to black
    SDL_RenderClear(this->_renderer); // clear window
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255); // set to current color
}

void Arcade::Display::SDL::update()
{
    SDL_Event event;

    this->_events.assign(SystemKeys::SYSKEYS_END, false);
    this->_keyCode = '\0';
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            auto found = std::find(this->_libKeys.begin(), this->_libKeys.end(), event.key.keysym.sym);
            if (found != this->_libKeys.end()) {
                this->_events[std::distance(this->_libKeys.begin(), found)] = true;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                this->_keyCode = '\b';
            }
        }
        if (event.type == SDL_TEXTINPUT) {
            this->_keyCode = event.text.text[0];
            memset(event.text.text, '\0', SDL_TEXTINPUTEVENT_TEXT_SIZE);
        }
    }
}

void Arcade::Display::SDL::render() const
{
    SDL_Delay(1000 / 60);
    SDL_RenderPresent(this->_renderer);
}

char Arcade::Display::SDL::getKeyCode() const
{
    if (this->_keyCode == '\b')
        return '\b';
    if (this->_keyCode < ' ' || this->_keyCode > 'z')
        return '\0';
    return this->_keyCode;
}

void Arcade::Display::SDL::setColor(IDisplayModule::Colors color)
{
    this->_currentColor = color;
    SDL_SetRenderDrawColor(this->_renderer, this->_libColors.at(this->_currentColor).r, this->_libColors.at(this->_currentColor).g, this->_libColors.at(this->_currentColor).b, 255);
}

void Arcade::Display::SDL::putPixel(float x, float y) const
{
    this->putRect(x, y, 1, 1);
}

void Arcade::Display::SDL::putLine(float x1, float y1, float x2, float y2) const
{
    if (x1 < 0) {
        x1 *= -1;
        x2 *= -1;
        y1 *= -1;
        y2 *= -1;
    } else if (x1 >= 0) {
        x1 += (FULL_WIDTH - WIDTH) / 2;
        x2 += (FULL_WIDTH - WIDTH) / 2;
        y1 += (FULL_HEIGHT - HEIGHT) / 2;
        y2 += (FULL_HEIGHT - HEIGHT) / 2;
    }
    SDL_RenderDrawLine(this->_renderer, x1, y1, x2, y2);
}

void Arcade::Display::SDL::putRect(float x, float y, float w, float h) const
{
    SDL_Rect fillRect = {(int)x, (int)y, (int)w, (int)h};

    if (x < 0) {
        fillRect.x *= -1;
        fillRect.y *= -1;
    } else if (x >= 0) {
        fillRect.x += (FULL_WIDTH - WIDTH) / 2;
        fillRect.y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    SDL_RenderDrawRect(this->_renderer, &fillRect);
}

void Arcade::Display::SDL::putFillRect(float x, float y, float w, float h) const
{
    SDL_Rect fillRect = {(int)x, (int)y, (int)w, (int)h};

    if (x < 0) {
        fillRect.x *= -1;
        fillRect.y *= -1;
    } else if (x >= 0) {
        fillRect.x += (FULL_WIDTH - WIDTH) / 2;
        fillRect.y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    SDL_RenderFillRect(this->_renderer, &fillRect);
}

void Arcade::Display::SDL::putCircle(float x, float y, float radius) const
{
    int pk = 1 - radius;
    int px = 0;
    int py = radius;
    int oldPx = 0;
    int oldPy = radius;

    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    x += radius;
    y += radius;
    while (py > px) {
        SDL_RenderDrawPoint(this->_renderer, x + px, y + py);
        SDL_RenderDrawPoint(this->_renderer, x + px, y - py);
        SDL_RenderDrawPoint(this->_renderer, x - px, y - py);
        SDL_RenderDrawPoint(this->_renderer, x - px, y + py);
        SDL_RenderDrawPoint(this->_renderer, x + py, y + px);
        SDL_RenderDrawPoint(this->_renderer, x + py, y - px);
        SDL_RenderDrawPoint(this->_renderer, x - py, y - px);
        SDL_RenderDrawPoint(this->_renderer, x - py, y + px);
        if (pk >= 0)
            py--;
        px++;
        pk = pk + (2 * (oldPx + 1)) + (pow(py, 2) - pow(oldPy, 2)) - (py - oldPy) + 1;
        oldPx = px;
        oldPy = py;
    }
}

void Arcade::Display::SDL::putFillCircle(float x, float y, float radius) const
{
    int pk = 1 - radius;
    int px = 0;
    int py = radius;
    int oldPx = 0;
    int oldPy = radius;

    this->putCircle(x, y, radius);
    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    x += radius;
    y += radius;
    while (py > px) {
        SDL_RenderDrawLine(this->_renderer, x - px, y - py, x + px, y - py);
        SDL_RenderDrawLine(this->_renderer, x - px, y - py, x + px, y - py);
        SDL_RenderDrawLine(this->_renderer, x - py, y + px, x + py, y + px);
        SDL_RenderDrawLine(this->_renderer, x - py, y - px, x + py, y - px);
        SDL_RenderDrawLine(this->_renderer, x - px, y + py, x + px, y + py);
        if (pk >= 0)
            py--;
        px++;
        pk = pk + (2 * (oldPx + 1)) + (pow(py, 2) - pow(oldPy, 2)) - (py - oldPy) + 1;
        oldPx = px;
        oldPy = py;
    }
}

void Arcade::Display::SDL::putText(const std::string &text, unsigned int size, float x, float y) const
{
    SDL_Surface *textSurface;
    SDL_Rect textRect;
    SDL_Texture *texture;

    if (this->_fonts->find(size) == this->_fonts->end()) {
        TTF_Font *newFont = TTF_OpenFont("./assets/pixelmix_bold.ttf", size);
        if (newFont == nullptr)
            throw Arcade::Exceptions::BadFileException("Cannot load font", "SDL::putText");
        this->_fonts->insert({size, newFont});
    }
    if (x < 0) {
        x *= -1;
        y *= -1;
    } else if (x >= 0) {
        x += (FULL_WIDTH - WIDTH) / 2;
        y += (FULL_HEIGHT - HEIGHT) / 2;
    }
    textSurface = TTF_RenderText_Solid(this->_fonts->find(size)->second, text.c_str(), this->_libColors.at(this->_currentColor));
    if (textSurface == nullptr)
        throw Arcade::Exceptions::BadInstanciationException("Text surface creation failed.", "SDL::putText");
    texture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    textRect.x = (int)x;
    textRect.y = (int)y;
    textRect.h = 0;
    textRect.w = 0;
    SDL_FreeSurface(textSurface);
    SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(this->_renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
}
