# Arcade

**Arcade** is a **gaming platform**: a program that lets the user **choose a game** to play and keeps a register of player scores.  

**Compatibility**: Linux *only*.

**Group members:**  
  - [@HeyShafty](https://github.com/HeyShafty)
  - [@Kilio22](https://github.com/Kilio22)
  - [@poll-an](https://github.com/poll-an)

This project provides *3 different graphical libraries implementation* which can be used to render games: **SFML**, **SDL2** and **Ncurses**.  
It provides *2 games* too: **Pacman** & **Snake**.  
When compiling the project, each graphical library is generated as a shared library in the `lib` folder, the games are generated as shared libraries too but in the `games` folder.   

During runtime, you'll be able to play (of course) and to **switch between libraries and games** using appropriates keys of your keyboard (you can find which key to use in the main menu of the arcade machine).  

The real challenge of this project: **load dynamic libraries** at runtime (and consequently not linking the `arcade` binary with any graphical library or implementing games directly in it).  
To do that, we've done an **abstraction** for graphical libraries and games. Each must respectively implements **IDisplayModule** interface or **IGameModule** interface.  
You'll find more about our architecture in **the documentation** which can be found in the `doc` folder: `ArcadeDoc.pdf`.

# How to run it ?
Clone the repository and go to the root of it, make sure that **SFML 2.5**, **SDL2** and **Ncurses** graphical libraries are installed, if not, please install them using your package manager.  

After that use this command to compile the project:
```sh
$> make
```
To start the arcade machine, you need to give a graphical library as argument:
 ```sh
 $> ./arcade <path_to_lib>
 ```
 Exemple:
```sh
 $> ./arcade ./lib/lib_arcade_sfml.so
 ```
 
 # How to create your own game or graphical library ?
 In order to do that, please **read the `ArcadeDoc.pdf`** which can be found in the `doc` folder.
