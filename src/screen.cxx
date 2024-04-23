#include "screen.hxx"
#include "block.hxx"
#include <cstdio>

void
Screen::flush(){
	HIDE_CURSOR;
	CLEAR_SCREEN;
	DRAW_BOUNDARY_LINE;
	for(signed line = 0; line < SCREEN_HEIGHT; ++line)
		DRAW_BODY_LINE;
	DRAW_BOUNDARY_LINE;
}

void
Screen::show(){
	START_DRAW;
	for(auto const& line: status){
		if(line.none()) DRAW_BODY_LINE;
		else{
			for(unsigned i = 0; i < SCREEN_WIDTH; ++i){
				if(line.test(i)) putchar(BLOCK);
				else putchar(' ');
			}
		}
	}
}