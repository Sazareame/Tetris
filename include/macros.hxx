#ifndef MACROS_HXX_
#define MACROS_HXX_

#define SCREEN_HEIGHT 20
#define SCREEN_WIDTH 10

#define DRAW_ONE_LINE_SPACE  puts("                    ")
#define DRAW_BOUNDARY_LINE puts("@@@@@@@@@@@@@@@@@@@@@@")
#define DRAW_BODY_LINE puts("@                    @")

#define CLEAR_SCREEN printf("\x1b[2J")
#define HIDE_CURSOR printf("\x1b[?25l")
#define SHOW_CURSOR printf("\x1b[?25h")
#define SCROLL_UP(n) puts("\x1b[20S")
#define SCROLL_DOWN(n) puts("\x1b[20T")
#define START_DRAW puts("\x1b[2;2H")

#endif