#include "block.hxx"
#include "block_type.hxx"
#include "macros.hxx"

Tetrominoes::Tetrominoes(int kind)
: index(kind), status(tetros[pose][kind]){
	hori_pos = 4;
	set_hw();
	colour = index;
}

Tetrominoes::Tetrominoes(int kind, int _colour)
: index(kind), colour(_colour), status(tetros[pose][kind]){
	hori_pos = 4;
	set_hw();
}

void
Tetrominoes::set_hw(){
	if(status >> 12){
		height = 4;
		width = 1;
	}else if(status >> 8){
		height = 3;
		width = 2;
	}else{
		height = 2;
		if(status == 0x0033)
			width = 2;
		else
			width = 3;
	}
}

void
Tetrominoes::drop(){
	++vert_pos;
}

void
Tetrominoes::slide_left(){
	if(hori_pos + width >= SCREEN_WIDTH) return;
	++hori_pos;
}

void
Tetrominoes::slide_right(){
	if(hori_pos == 0) return;
	--hori_pos;
}

void
Tetrominoes::rotate(){
	height = height ^ width;
	width = height ^ width;
	height = height ^ width;

	if(pose < 3)
		++pose;
	else
		pose = 0;

	if(hori_pos + width >= SCREEN_WIDTH){
		hori_pos = SCREEN_WIDTH - width;
	}

	status = tetros[pose][index];
}

int
Tetrominoes::get_hori_pos()const{
	return hori_pos;
}

int
Tetrominoes::get_vert_pos()const{
	return vert_pos;
}

uint16_t
Tetrominoes::get_status()const{
	return status;
}

int
Tetrominoes::get_colour()const{
	return colour;
}