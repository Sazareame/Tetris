## Tetrisxx - A Simple cmd Line Tetris Game Wirt in CXX

### Intro
This little programme is a Tetris game running on terminal.   

The archive only contains source files. To build it, please run   

```cmake -S . -B <path_to_config> && cmake --build <path_to_config>```     

### Game Rules

`a` and `d` for moving the block left and right     
`w` for rotating the block     
`s` for accelarating     
**NOTE that arrow keys are not supported. Perhaps it will be fixed sometimes in the future**     

**NOTE that the performance on WSL might be a little unstable**     

**If you choose to build it on Windows, I recommend you use MSVC or build via Visual Studio instead of GCC/Clang due to they probably resulting in abnormal refreshing**

*Thanks for playing (or testing) this tiny game. It is currently a half-completed programme, I shall progressively perfect it.*
