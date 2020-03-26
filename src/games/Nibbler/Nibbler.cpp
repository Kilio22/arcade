/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include "games/Nibbler.hpp"

extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<Arcade::Games::Nibbler>();
}

Arcade::Games::Nibbler::Nibbler()
    : AGameModule("Nibbler")
{
    this->reset();
}

void Arcade::Games::Nibbler::reset()
{
    this->framesToStep = 10;
    this->frameCount = 0;
    this->direction = UP;
    this->lastDirection = UP;
    this->_currentScore = 0;
    this->spawnFruit();
    this->snake = {{10, 10}, {10, 11}, {10, 12}, {10, 13}};
}

void Arcade::Games::Nibbler::spawnFruit()
{
    this->fruit = {1 + std::rand() % (this->xTiles - 2), 1 + std::rand() % (this->yTiles - 2)};
    while (std::find(this->snake.begin(), this->snake.end(), this->fruit) != this->snake.end())
        this->fruit = {1 + std::rand() % (this->xTiles - 2), 1 + std::rand() % (this->yTiles - 2)};
}

bool Arcade::Games::Nibbler::isDead()
{
    auto it = this->snake.begin();

    if (it->first == 0 || it->first == this->xTiles - 1)
        return true;
    if (it->second == 0 || it->second == this->yTiles - 1)
        return true;
    if (std::find(++it, this->snake.end(), *it) != this->snake.end())
        return true;
    return false;
}

void Arcade::Games::Nibbler::update(const Arcade::Display::IDisplayModule &displayModule)
{
    this->frameCount += displayModule.getDelta();

    this->updateDirection(displayModule);
    if (displayModule.isKeyPressed(Display::IDisplayModule::Keys::SPACE))
        this->frameCount = this->framesToStep;
    if (this->frameCount >= this->framesToStep) {
        this->updateSnake();
        if (this->isDead() == true) {
            this->addToBestScores(this->_currentScore);
            this->reset();
        }
    }
}

void Arcade::Games::Nibbler::updateDirection(const Arcade::Display::IDisplayModule &displayModule)
{
    if (displayModule.isKeyPressedOnce(Display::IDisplayModule::Q) && this->lastDirection != RIGHT) {
        this->direction = LEFT;
    } else if (displayModule.isKeyPressedOnce(Display::IDisplayModule::D) && this->lastDirection != LEFT) {
        this->direction = RIGHT;
    } else if (displayModule.isKeyPressedOnce(Display::IDisplayModule::Z) && this->lastDirection != DOWN) {
        this->direction = UP;
    } else if (displayModule.isKeyPressedOnce(Display::IDisplayModule::S) && this->lastDirection != UP) {
        this->direction = DOWN;
    }
}

void Arcade::Games::Nibbler::updateSnake()
{
    auto newHead = this->snake.front();

    switch (this->direction) {
        default:
        case LEFT:
            newHead.first -= 1;
            break;

        case RIGHT:
            newHead.first += 1;
            break;

        case UP:
            newHead.second -= 1;
            break;

        case DOWN:
            newHead.second += 1;
            break;
    }
    this->lastDirection = this->direction;
    if (newHead == this->fruit) {
        this->spawnFruit();
        this->_currentScore += 100;
        if (this->_currentScore % 500 == 0 && this->framesToStep > 1)
            this->framesToStep -= .5;
    } else
        this->snake.pop_back();
    this->snake.push_front(newHead);
    this->frameCount = 0;
}

void Arcade::Games::Nibbler::render(Arcade::Display::IDisplayModule &displayModule) const
{
    this->drawBorder(displayModule);
    this->drawFruit(displayModule);
    this->drawSnake(displayModule);
    this->drawControls(displayModule);
}

void Arcade::Games::Nibbler::drawBorder(Arcade::Display::IDisplayModule &displayModule) const
{
    displayModule.setColor(Display::IDisplayModule::Colors::WHITE);
    for (int i = 0; i < this->xTiles; ++i) {
        displayModule.putFillRect(i * xSize, 0, xSize, ySize);
        displayModule.putFillRect(i * xSize, HEIGHT - ySize * 2, xSize, ySize);
    }
    for (int i = 1; i < this->yTiles - 1; ++i) {
        displayModule.putFillRect(0, i * ySize, xSize, ySize);
        displayModule.putFillRect(WIDTH - xSize, i * ySize, xSize, ySize);
    }
}

void Arcade::Games::Nibbler::drawFruit(Arcade::Display::IDisplayModule &displayModule) const
{
    displayModule.setColor(Display::IDisplayModule::Colors::RED);
    displayModule.putFillRect(this->fruit.first * xSize, this->fruit.second * ySize, xSize, ySize);
}

void Arcade::Games::Nibbler::drawSnake(Arcade::Display::IDisplayModule &displayModule) const
{
    displayModule.setColor(Display::IDisplayModule::Colors::GREEN);
    auto snakePart = this->snake.begin();

    displayModule.putRect(snakePart->first * xSize, snakePart->second * ySize, xSize, ySize);
    ++snakePart;
    while (snakePart != this->snake.end()) {
        displayModule.putFillRect(snakePart->first * xSize, snakePart->second * ySize, xSize, ySize);
        ++snakePart;
    }
}

void Arcade::Games::Nibbler::drawControls(Arcade::Display::IDisplayModule &displayModule) const
{
    displayModule.setColor(Display::IDisplayModule::Colors::MAGENTA);
    displayModule.putText("SPACE for boost!", 10, WIDTH / 2 - 65, HEIGHT - 13);
}
