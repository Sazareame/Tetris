#ifndef BLOCK_HXX_
#define BLOCK_HXX_

#include <bitset>
#include "macros.hxx"

#define BLOCK 'O'
#define BOUND '@'

class Tetrominoes{
	// position of the right bottom of the tetro.
	// coordinate origin is the right top of the screen.
	int vert_pos = -1;
	int hori_pos;

	// height and width of the tertrominoes
	int const height = 0;
	int const width = 0; 
	uint16_t status;

public:
Tetrominoes(uint16_t _status, int hori);

void drop();
void slide_left();
void slide_right();
void rotate();
int get_vert_pos()const;
int get_hori_pos()const;
uint16_t get_status()const;
};







#endif