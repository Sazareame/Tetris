#ifndef MACROS_HXX_
#define MACROS_HXX_

#define SCREEN_HEIGHT 20
#define SCREEN_WIDTH 10

#ifdef TETRIS_GUI_COLOUR
#define PUTBLOCK printf("  ")
#define PUTWALL  printf("\x1b[45m \x1b[0m")
#define DRAW_BOUNDARY_LINE   printf("\x1b[45m                      \x1b[0m")
#define DRAW_BODY_LINE       printf("\x1b[45m \x1b[0m                    \x1b[45m \x1b[0m\n")
#else
#define PUTBLOCK printf("O ")
#define PUTWALL  printf("+")
#define DRAW_BOUNDARY_LINE   printf("======================")
#define DRAW_BODY_LINE       printf("+                    +\n")
#endif
#define PUTSPACE printf("\x1b[0m\x1b[1m  ")

#define DRAW_ONE_LINE_SPACE  printf("                    ")

#define CLEAR_SCREEN   printf("\x1b[2J")
#define HIDE_CURSOR    printf("\x1b[?25l")
#define SHOW_CURSOR    printf("\x1b[?25h")
#define SCROLL_UP(n)   printf("\x1b[20S")
#define SCROLL_DOWN(n) printf("\x1b[20T")
#define START_DRAW     printf("\x1b[2;1H")
#define DRAW_NEXT_LINE printf("\x1b[1E")

#define RESET_ALL printf("\x1b[0m")
#define MAKE_BOLD printf("\x1b[1m")

#endif