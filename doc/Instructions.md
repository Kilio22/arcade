# How to implement your own game / library

## Game

- First, you wanna create a c++ class implementing the [IGameModule](@ref Arcade.Games.IGameModule) interface.
- Next you wanna compile it into a dynamic library (.so file).
- Put that library file in the `games/` folder located at the root of the arcade repository.

Every class contained by the libraries located in the `games/` folder are going to be instanciated thanks to the symbol `createLib` that your library **must** contain.  

```cpp
extern "C" std::unique_ptr<Arcade::Games::IGameModule> createLib(void)
{
    return std::make_unique<MyGameModule>();
}
```

## Library

- First, you wanna create a c++ class implementing the [IDisplayModule](@ref Arcade.Display.IDisplayModule) interface.
- Next you wanna compile it into a dynamic library (.so file).
- Put that library file in the `lib/` folder located at the root of the arcade repository.

Every class contained by the libraries located in the `lib/` folder are going to be instanciated thanks to the symbol `createLib` that your library **must** contain.  

```cpp
extern "C" std::unique_ptr<Arcade::Display::IDisplayModule> createLib(void)
{
    return std::make_unique<MyDisplayModule>();
}
```
