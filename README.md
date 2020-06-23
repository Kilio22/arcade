# Arcade

**Arcade** is a **gaming platform**: a program that lets the user **choose a game** to play and keeps a register of player scores.  

**Compatibility**: Linux only.

**Group members:**  
  - [@HeyShafty](https://github.com/HeyShafty)
  - [@Kilio22](https://github.com/Kilio22)
  - [@poll-an](https://github.com/poll-an)

This project provides 3 different graphical libraries implementation which can be used to render games: **SFML**, **SDL2** and **Ncurses**.  
It provides 2 games too: **Pacman** & **Snake**.  
When compiling the project, each library implementation is generated as a shared library in the `lib` folder, the games are generated as shared libraries too but in the `games` folder.   

During runtime, you'll be able to play of course and to **switch between libraries and games** using appropriates keys (you can find which key to use in the main menu of the arcade machine).

# How to use it ?
Clone the repository and go to the root of it, make sure that **SFML 2.5**, **SDL2** and **Ncurses** graphical libraries are installed, if not, please install them using your package manager.
After that use this command to compile the project:
```sh
$> make
```
To start the arcade machine, you need to give a library as argument:
 ```sh
 $> ./arcade <path_to_lib>
 ```
 Exemple:
```sh
 $> ./arcade ./lib/lib_arcade_sfml.so
 ```
 
 # How to create your own game or graphical library ?
 In order to do that, please **read the `ArcadeDoc.pdf`** which can be found in the `doc` folder. You'll find some explanations of our architecture for the project and all answers to your questions.
