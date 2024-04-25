#ifndef BLOCK_HXX_
#define BLOCK_HXX_

#include <stdint.h>

#define BOUND '@'

class Tetrominoes{
	// position of the right bottom of the tetro.
	// coordinate origin is the right top of the screen.
	int vert_pos = -1;
	int hori_pos;

	// height and width of the tertrominoes
	int height = 0;
	int width = 0; 
	int pose = 0;
	int index;
	int colour;
	uint16_t status;

	void set_hw();

public:
Tetrominoes(int kind);
Tetrominoes(int kind, int _colour);

void drop();
void slide_left();
void slide_right();
void rotate();
int get_vert_pos()const;
int get_hori_pos()const;
uint16_t get_status()const;
int get_colour()const;
};

#endif