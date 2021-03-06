/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include <algorithm>
#include <cctype>
#include "arcade.h"
#include "DLLoader.hpp"
#include "Core.hpp"
#include "Logger.hpp"
#include "Exceptions/BadFileException.hpp"
#include "Exceptions/InvalidLibraryException.hpp"

const char *defaultUsername = "Michel";

Arcade::Core::Core(const std::string &startLibraryPath)
    : username(defaultUsername),
    libraries(DLLoader<Display::IDisplayModule>::getInstance().getLibraries(ARCADE_LIB_PATH)),
    games(DLLoader<Games::IGameModule>::getInstance().getLibraries(ARCADE_GAMES_PATH)),
    iGame(0),
    displayModule(DLLoader<Display::IDisplayModule>::getInstance().loadLibrary(startLibraryPath)),
    gameModule(nullptr)
{
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Given library could not be loaded.", "Core::Core");
    if (this->games.empty())
        throw Exceptions::InvalidLibraryException("There are no available games to play.", "Core::Core");

    auto startLibraryRelativePath = "./lib" + startLibraryPath.substr(startLibraryPath.find_last_of("/"));
    auto it = std::find_if(this->libraries.begin(), this->libraries.end(), [startLibraryRelativePath](auto &infos){ return infos.path == startLibraryRelativePath; });
    if (it == this->libraries.end())
        throw Exceptions::BadFileException("Argument does not match with any existing library.", "Core::Core");
    this->iLib = std::distance(this->libraries.begin(), it);

    Logger::log(Logger::DEBUG, "Library count: ", this->libraries.size());
    Logger::log(Logger::DEBUG, "Library name: ", this->displayModule->getLibName(), " [", this->iLib, "]");
    Logger::log(Logger::DEBUG, "Game count: ", this->games.size());
}

void Arcade::Core::play()
{
    this->displayModule->open();
    while (this->displayModule->isOpen() == true) {
        this->displayModule->setColor(Display::IDisplayModule::Colors::DEFAULT);
        this->displayModule->update();
        this->displayModule->clear();
        if (this->displayModule->shouldExit())
            return;
        if (this->displayModule->switchToNextLib() == true)
            this->switchLibrary(NEXT);
        else if (this->displayModule->switchToPreviousLib() == true)
            this->switchLibrary(PREV);
        if (this->gameModule == nullptr) {
            this->menuEvents();
            this->menuDisplay();
        } else {
            this->games[this->iGame].scores = this->gameModule->getBestScores();
            if (this->displayModule->shouldGoToMenu()) {
                this->gameModule.reset();
                continue;
            }
            this->gameEvents();
            this->gameDisplay();
        }
        this->displayOverlay();
        this->displayModule->render();
    }
}

void Arcade::Core::menuEvents()
{
    if (this->displayModule->isKeyPressedOnce(Display::IDisplayModule::Keys::ENTER) == true) {
        this->gameModule = DLLoader<Games::IGameModule>::getInstance().loadLibrary(this->games[this->iGame].path);
        if (this->gameModule == nullptr)
            throw Exceptions::InvalidLibraryException("Unexpected error while loading game.", "Core::menuEvents");
        this->gameModule->setPlayerName(this->username);
        if (this->gameModule->loadFromFile() == false)
            Logger::log(Logger::ERROR, "Could not load scores.");
        Logger::log(Logger::DEBUG, "Selected game: ", this->gameModule->getLibName(), " [", this->iGame, "]");
        return;
    }
    if (this->displayModule->switchToNextGame() == true
    || this->displayModule->isKeyPressedOnce(Display::IDisplayModule::Keys::UP) == true) {
        this->iGame = (this->iGame + 1) % this->games.size();
    }
    if (this->displayModule->switchToPreviousGame() == true
    || this->displayModule->isKeyPressedOnce(Display::IDisplayModule::Keys::DOWN) == true) {
        --this->iGame;
        if (this->iGame < 0)
            this->iGame = this->games.size() - 1;
    }
    auto key = this->displayModule->getKeyCode();
    if (key != '\0') {
        if (key == '\b') {
            if (this->username.empty() == false)
                this->username = this->username.substr(0, this->username.length() - 1);
        } else if (std::isalnum(static_cast<unsigned char>(key)) != false)
            this->username.append(std::string(1, key));
    }
}

void Arcade::Core::menuDisplay() const
{
    int y = 0;

    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_BLUE);
    this->displayModule->putFillRect(0, 0, WIDTH, HEIGHT);
    this->displayModule->setColor(Display::IDisplayModule::Colors::CYAN);
    for (int i = this->games.size() - 1; i >= 0; --i) {
        if (this->iGame == i)
            this->displayModule->setColor(Display::IDisplayModule::Colors::BLUE);
        this->displayModule->putText(this->games[i].name, 20, 30, y += 30);
        if (this->iGame == i)
            this->displayModule->setColor(Display::IDisplayModule::Colors::CYAN);
    }
}

void Arcade::Core::gameEvents()
{
    if (this->displayModule->shouldBeRestarted() == true)
        this->gameModule->reset();
    if (this->displayModule->switchToNextGame() == true)
        this->switchGame(NEXT);
    else if (this->displayModule->switchToPreviousGame() == true)
        this->switchGame(PREV);
}

void Arcade::Core::gameDisplay() const
{
    this->gameModule->update(*this->displayModule);
    this->displayModule->setColor(Display::IDisplayModule::Colors::DARK_GRAY);
    this->displayModule->putFillRect(0, 0, WIDTH, HEIGHT);
    this->gameModule->render(*this->displayModule);
}

void Arcade::Core::displayOverlay() const
{
    int y = -70;

    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_GREEN);
    this->displayModule->putText("Player: " + this->username + (this->gameModule == nullptr ? "<" : ""), 20, -10, -10);
    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_RED);
    this->displayModule->putText("Available libraries: " + std::to_string(this->libraries.size()), 20, -10, y);
    for (int i = 0; i < (int)this->libraries.size(); ++i) {
        if (this->iLib == i) {
            this->displayModule->setColor(Display::IDisplayModule::Colors::RED);
            this->displayModule->putText("    > " + this->libraries[i].name, 20, -10, y -= 40);
            this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_RED);
        } else
            this->displayModule->putText("    " + this->libraries[i].name, 20, -10, y -= 40);
    }
    if (this->gameModule != nullptr) {
        this->displayModule->setColor(Display::IDisplayModule::Colors::YELLOW);
        this->displayModule->putText(this->gameModule->getLibName() + ": " + std::to_string(this->gameModule->getScore().second), 20, -(FULL_WIDTH / 2) + 75, -50);
    }
    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_YELLOW);
    this->displayModule->putText("Best scores: " + std::to_string(this->games[this->iGame].scores.size()), 20, -10, y -= 60);
    if (this->games[this->iGame].scores.empty())
        this->displayModule->putText("    None yet...", 20, -10, y -= 40);
    else {
        for (auto &score : this->games[this->iGame].scores)
            this->displayModule->putText("    " + score.first + ": " + std::to_string(score.second), 20, -10, y -= 40);
    }
    this->displayControls();
}

void Arcade::Core::displayControls() const
{
    int y = 0;
    std::ostringstream oss;
    char str[40];

    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_GRAY);
    sprintf(str, "%39s", "Press R to restart the game.");
    this->displayModule->putText(str, 15, -1350, y -= 10);
    sprintf(str, "%39s", "Press ESCAPE to quit Arcade.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
    sprintf(str, "%39s", "Press M to go back to the menu.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
    sprintf(str, "%39s", "Press F1 to use the previous library.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
    sprintf(str, "%39s", "Press F2 to use the next library.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
    sprintf(str, "%39s", "Press F3 to use the previous game.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
    sprintf(str, "%39s", "Press F4 to use the next game.");
    this->displayModule->putText(str, 15, -1350, y -= 30);
}

void Arcade::Core::switchLibrary(Direction direction)
{
    if (this->libraries.size() <= 1)
        return;
    Logger::log(Logger::DEBUG, "Changing library ", direction);
    if (direction == PREV) {
        --this->iLib;
        if (this->iLib < 0)
            this->iLib = this->libraries.size() - 1;
    } else {
        this->iLib = (this->iLib + 1) % this->libraries.size();
    }
    this->displayModule = DLLoader<Display::IDisplayModule>::getInstance().loadLibrary(this->libraries[this->iLib].path);
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching library.", "Core::switchLibrary");
    this->displayModule->open();
    Logger::log(Logger::DEBUG, "New library: ", this->displayModule->getLibName(), " [", this->iLib, "]");
}

void Arcade::Core::switchGame(Direction direction)
{
    if (this->games.size() <= 1)
        return;
    Logger::log(Logger::DEBUG, "Changing game ", direction);
    if (direction == PREV) {
        --this->iGame;
        if (this->iGame < 0)
            this->iGame = this->games.size() - 1;
    } else {
        this->iGame = (this->iGame + 1) % this->games.size();
    }
    this->gameModule = DLLoader<Games::IGameModule>::getInstance().loadLibrary(this->games[this->iGame].path);
    if (this->gameModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching game.", "Core::switchGame");
    this->gameModule->setPlayerName(this->username);
    if (this->gameModule->loadFromFile() == false)
        Logger::log(Logger::ERROR, "Could not load scores.");
    Logger::log(Logger::DEBUG, "New game: ", this->gameModule->getLibName(), " [", this->iGame, "]");
    auto scores = this->gameModule->getBestScores();
}
