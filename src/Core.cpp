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
#include "Exceptions/InvalidLibraryException.hpp"

const char *defaultUsername = "Michel Forevertonight";

Arcade::Core::Core(const std::string &startLibraryPath)
    : username(defaultUsername),
    libraries(DLLoader::getInstance().getLibraries(ARCADE_LIB_PATH)),
    games(DLLoader::getInstance().getLibraries(ARCADE_GAMES_PATH)),
    iGame(CORE_MENU_INDEX),
    displayModule(DLLoader::getInstance().loadLibrary<Display::IDisplayModule>(startLibraryPath)),
    gameModule(nullptr)
{
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Given library could not be loaded.", "Core::Core");
    // if (this->games.empty())
    //     throw Exceptions::InvalidLibraryException("There are no available games to play.", "Core::Core");
    this->iLib = std::distance(this->libraries.begin(),
                               std::find(this->libraries.begin(),
                                         this->libraries.end(),
                                         startLibraryPath));
    std::cerr << "[DEBUG] Library count : " << this->libraries.size() << std::endl;
    std::cerr << "[DEBUG] Game count : " << this->games.size() << std::endl;
}

void Arcade::Core::play()
{
    while (this->displayModule->isOpen() == true) {
        this->displayModule->clear();
        this->displayModule->update();
        if (this->displayModule->shouldExit())
            return;
        if (this->displayModule->switchToNextLib() == true)
            this->switchLibrary(NEXT);
        if (this->displayModule->switchToPreviousLib() == true)
            this->switchLibrary(PREV);
        if (this->displayModule->switchToNextGame() == true)
            this->switchGame(NEXT);
        if (this->displayModule->switchToPreviousGame() == true)
            this->switchGame(PREV);
        if (this->iGame == CORE_MENU_INDEX) {
            this->displayModule->putText("Hello, World!", 30, 100, 100);
            this->displayModule->render();
        } else {
            this->gameModule->update();
            this->gameModule->render(*this->displayModule);
        }
    }
}

// Pas encore testé (il faudrait une autre librarie qui peut load)
void Arcade::Core::switchLibrary(Direction direction)
{
    if (this->libraries.size() == 1)
        return;
    std::cerr << "[DEBUG] Changing library " << direction << std::endl;
    if (direction == PREV) {
        --this->iLib;
        if (this->iLib < 0)
            this->iLib = this->libraries.size() - 1;
    } else {
        this->iLib = (this->iLib + 1) % this->libraries.size();
    }
    this->displayModule = DLLoader::getInstance().loadLibrary<Display::IDisplayModule>(this->libraries[this->iLib]);
    if (this->displayModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching library.", "Core::switchLibrary");
}

// Pas encore testé (on a pas de jeux lel)
void Arcade::Core::switchGame(Direction direction)
{
    if (this->games.size() == 1)
        return;
    if (this->iGame == -1)
        return;
    std::cerr << "[DEBUG] Changing game " << direction << std::endl;
    if (direction == PREV) {
        --this->iGame;
        if (this->iGame < 0)
            this->iGame = this->games.size() - 1;
    } else {
        this->iGame = (this->iGame + 1) % this->games.size();
    }
    this->gameModule = DLLoader::getInstance().loadLibrary<Games::IGameModule>(this->games[this->iGame]);
    if (this->gameModule == nullptr)
        throw Exceptions::InvalidLibraryException("Unexpected error while switching game.", "Core::switchGame");
}
