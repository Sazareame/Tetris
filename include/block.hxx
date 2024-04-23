#ifndef BLOCK_HXX_
#define BLOCK_HXX_

#include <bitset>
#include "macros.hxx"

#define BLOCK '#'
#define BOUND '@'

class Tetrominoes{
	int vert_pos = 0; // position(row) of the lowest block

	// height and width of the tertrominoes
	int const height;
	int const width; 
	std::bitset<SCREEN_WIDTH> hori_pos; // status of the lowest line
};







#endif