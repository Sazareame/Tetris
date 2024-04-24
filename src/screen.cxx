#include "screen.hxx"
#include "block.hxx"
#include <cstdio>

void
Screen::flush(){
	// HIDE_CURSOR;
	fflush(stdout);
	CLEAR_SCREEN;
	DRAW_BOUNDARY_LINE;
	for(signed line = 0; line < SCREEN_HEIGHT; ++line)
		DRAW_BODY_LINE;
	DRAW_BOUNDARY_LINE;
}

void
Screen::show(std::deque<uint16_t> const& status){
	fflush(stdout);
	START_DRAW;
	fflush(stdout);
	DRAW_BOUNDARY_LINE;
	for(auto& line: status){
		putchar('+');
		if((line & 0x03ff) == 0){
			DRAW_ONE_LINE_SPACE;
			putchar('+');
			DRAW_NEXT_LINE;
		}
		else{
			for(uint16_t i = 0x0200; i > 0; i >>= 1){
				if(i & line)
					PUTBLOCK
				else
					PUTSPACE;
			}
			putchar('+');
			DRAW_NEXT_LINE;
		}
		fflush(stdout);
	}
	DRAW_BOUNDARY_LINE;
	fflush(stdout);
}