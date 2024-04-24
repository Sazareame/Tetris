#ifndef MACROS_HXX_
#define MACROS_HXX_

#define SCREEN_HEIGHT 20
#define SCREEN_WIDTH 10

#define PUTBLOCK {putchar('O');putchar(' ');}
#define PUTSPACE {putchar(' ');putchar(' ');}

#define DRAW_ONE_LINE_SPACE  printf("                    ")
#define DRAW_BOUNDARY_LINE   printf("======================\n")
#define DRAW_BODY_LINE       printf("+                    +\n")

#define CLEAR_SCREEN   printf("\x1b[2J")
#define HIDE_CURSOR    printf("\x1b[?25l")
#define SHOW_CURSOR    printf("\x1b[?25h")
#define SCROLL_UP(n)   printf("\x1b[20S")
#define SCROLL_DOWN(n) printf("\x1b[20T")
#define START_DRAW     printf("\x1b[2;1H")
#define DRAW_NEXT_LINE printf("\x1b[1E")

#endif