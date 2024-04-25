## Tetrisxx - A Simple cmd Line Tetris Game Wirt in CXX

### Intro
This little programme is a Tetris game running on terminal.     

The programme assumes that your terminal has 8-colour gui. If unfortunatly your PC DOSE NOT support that, which is hard to believe in 2024, you can switch to pure ascii mode by commet (or just delete)     

```add_definitions(-DTETRIS_GUI_COLOUR)```      

in `CMakeLists.txt`.

The archive only contains source files. To build it, please run   

```cmake -S . -B <path_to_config> && cmake --build <path_to_config>```     

### Game Rules

`a` and `d` for moving the block left and right     
`w` for rotating the block     
`s` for accelarating     
**NOTE that arrow keys are not supported. Perhaps it will be fixed sometimes in the future**     

*Thanks for playing (or testing) this tiny game. It is currently a half-completed programme, I shall progressively perfect it.*
