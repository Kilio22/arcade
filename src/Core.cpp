/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include <algorithm>
#include "arcade.h"
#include "DLLoader.hpp"
#include "Core.hpp"
#include "Logger.hpp"
#include "Exceptions/BadFileException.hpp"
#include "Exceptions/InvalidLibraryException.hpp"

const char *defaultUsername = "Michel Forevertonight";

Arcade::Core::Core(const std::string &startLibraryPath)
    : username(defaultUsername),
    libraries(DLLoader::getInstance().getLibraries<Display::IDisplayModule>(ARCADE_LIB_PATH)),
    games(DLLoader::getInstance().getLibraries<Games::IGameModule>(ARCADE_GAMES_PATH)),
    iGame(0),
    displayModule(DLLoader::getInstance().loadLibrary<Display::IDisplayModule>(startLibraryPath)),
    gameModule(nullptr)
{
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Given library could not be loaded.", "Core::Core");
    // if (this->games.empty())
    //     throw Exceptions::InvalidLibraryException("There are no available games to play.", "Core::Core");

    // TODEV: sometimes the find may not work even though the path is fine
    auto it = std::find_if(this->libraries.begin(), this->libraries.end(), [startLibraryPath](auto &pair){ return pair.first == startLibraryPath; });
    if (it == this->libraries.end())
        throw Exceptions::BadFileException("Argument does not match with any existing library.", "Core::Core");
    this->iLib = std::distance(this->libraries.begin(), it);

    Logger::log(Logger::DEBUG, "Library count: ", this->libraries.size());
    Logger::log(Logger::DEBUG, "Library name: ", this->displayModule->getLibName(), " [", this->iLib, "]");
    Logger::log(Logger::DEBUG, "Game count: ", this->games.size());
    // Logger::log(Logger::DEBUG, "[DEBUG] Game name: ", this->gameModule->getLibName());
}

void Arcade::Core::play()
{
    this->displayModule->open();
    while (this->displayModule->isOpen() == true) {
        this->displayModule->setColor(Display::IDisplayModule::Colors::DEFAULT);
        this->displayModule->clear();
        this->displayModule->update();
        if (this->displayModule->shouldExit())
            return;
        if (this->displayModule->shouldGoToMenu())
            this->gameModule.reset();
        if (this->displayModule->switchToNextLib() == true)
            this->switchLibrary(NEXT);
        if (this->displayModule->switchToPreviousLib() == true)
            this->switchLibrary(PREV);
        if (this->displayModule->switchToNextGame() == true)
            this->switchGame(NEXT);
        if (this->displayModule->switchToPreviousGame() == true)
            this->switchGame(PREV);
        this->displayOverlay();
        if (this->gameModule == nullptr) {
            this->menu();
            this->displayModule->render();
        } else {
            this->gameModule->update(*this->displayModule);
            this->gameModule->render(*this->displayModule);
        }
    }
}

void Arcade::Core::menu()
{
    if (this->displayModule->getKeyCode() != '\0') {
        if (this->displayModule->getKeyCode() == '\b' && this->username.empty() == false)
            this->username = this->username.substr(0, this->username.length() - 1);
        else if (this->displayModule->getKeyCode() != '\n')
            this->username.append(std::string(1, this->displayModule->getKeyCode()));
    }
    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_BLUE);
    this->displayModule->putFillRect((FULL_WIDTH - WIDTH) / 2, (FULL_HEIGHT - HEIGHT) / 2, WIDTH, HEIGHT);
    this->displayModule->setColor(Display::IDisplayModule::Colors::CYAN);
    int y = (FULL_HEIGHT - HEIGHT) / 2;
    for (int i = 0; i < 3; ++i) {
        if (this->iGame == i)
            this->displayModule->setColor(Display::IDisplayModule::Colors::BLUE);
        this->displayModule->putText("No games yet.", 20, (FULL_WIDTH - WIDTH) / 2 + 30, y += 30);
        if (this->iGame == i)
            this->displayModule->setColor(Display::IDisplayModule::Colors::CYAN);
    }
}

void Arcade::Core::displayOverlay() const
{
    std::vector<std::tuple<std::string, int>> xdd = {
        {"Jean-pol", 55555},
        {"Jean-patrick", 4444},
        {"Jean-pierre", 333},
        {"Jean-padernier", 22},
        {"Jean-putaing", 1},
    };
    int y = 70;

    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_GREEN);
    this->displayModule->putText("Player: " + this->username + (this->gameModule == nullptr ? "<" : ""), 20, 10, 10);
    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_RED);
    this->displayModule->putText("Available libraries: " + std::to_string(this->libraries.size()), 20, 10, y);
    for (int i = 0; i < (int)this->libraries.size(); ++i) {
        if (this->iLib == i) {
            this->displayModule->setColor(Display::IDisplayModule::Colors::RED);
            this->displayModule->putText("    > " + this->libraries[i].second, 20, 10, y += 40);
            this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_RED);
        } else
            this->displayModule->putText("    " + this->libraries[i].second, 20, 10, y += 40);
    }
    /* Pas encore de jeux xdxd */
    this->displayModule->setColor(Display::IDisplayModule::Colors::LIGHT_YELLOW);
    this->displayModule->putText("Scores: " + std::to_string(xdd.size()), 20, 10, y += 200);
        for (auto &score : xdd)
            this->displayModule->putText("    " + std::get<0>(score) + ": " + std::to_string(std::get<1>(score)), 20, 10, y += 40);
    /* Décommenter ci-dessous quand y'a des jeux xdxd */
    if (this->gameModule != nullptr) {
        auto scores = this->gameModule->getLatestScores();
        this->displayModule->putText("Scores: " + std::to_string(scores.size()), 20, 10, y += 60);
        for (auto &score : scores)
            this->displayModule->putText("    " + std::get<0>(score) + ": " + std::to_string(std::get<1>(score)), 20, 10, y += 40);
    }
    this->displayControls();
}

void Arcade::Core::displayControls() const
{
    int y = 0;
    std::ostringstream oss;
    char str[40];

    this->displayModule->setColor(Display::IDisplayModule::Colors::DARK_GRAY);
    sprintf(str, "%39s", "Press R to restart the game.");
    this->displayModule->putText(str, 15, 1350, y += 10);
    sprintf(str, "%39s", "Press ESCAPE to quit Arcade.");
    this->displayModule->putText(str, 15, 1350, y += 30);
    sprintf(str, "%39s", "Press M to go back to the menu.");
    this->displayModule->putText(str, 15, 1350, y += 30);
    sprintf(str, "%39s", "Press DOWN to use the previous game.");
    this->displayModule->putText(str, 15, 1350, y += 30);
    sprintf(str, "%39s", "Press UP to use the next game.");
    this->displayModule->putText(str, 15, 1350, y += 30);
    sprintf(str, "%39s", "Press LEFT to use the previous library.");
    this->displayModule->putText(str, 15, 1350, y += 30);
    sprintf(str, "%39s", "Press RIGHT to use the next library.");
    this->displayModule->putText(str, 15, 1350, y += 30);
}

// Pas encore testé (il faudrait une autre librarie qui peut load)
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
    this->displayModule = DLLoader::getInstance().loadLibrary<Display::IDisplayModule>(this->libraries[this->iLib].first);
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching library.", "Core::switchLibrary");
    this->displayModule->open();
    Logger::log(Logger::DEBUG, "New library: ", this->displayModule->getLibName(), " [", this->iLib, "]");
}

// Pas encore testé (on a pas de jeux lel)
void Arcade::Core::switchGame(Direction direction)
{
    if (this->games.size() <= 1)
        return;
    if (this->iGame == -1)
        return;
    Logger::log(Logger::DEBUG, "Changing game ", direction);
    if (direction == PREV) {
        --this->iGame;
        if (this->iGame < 0)
            this->iGame = this->games.size() - 1;
    } else {
        this->iGame = (this->iGame + 1) % this->games.size();
    }
    this->gameModule = DLLoader::getInstance().loadLibrary<Games::IGameModule>(this->games[this->iGame].first);
    if (this->gameModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching game.", "Core::switchGame");
    Logger::log(Logger::DEBUG, "New game: ", this->gameModule->getLibName(), " [", this->iGame, "]");
        auto scores = this->gameModule->getLatestScores();
}
