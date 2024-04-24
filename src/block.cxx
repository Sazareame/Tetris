#include "block.hxx"

Tetrominoes::Tetrominoes(uint16_t _status, int hori): status(_status){
	hori_pos = hori;
}

void
Tetrominoes::drop(){
	++vert_pos;
}

void
Tetrominoes::slide_left(){
	if(hori_pos + height >= SCREEN_WIDTH) return;
	++hori_pos;
}

void
Tetrominoes::slide_right(){
	if(hori_pos == 0) return;
	--hori_pos;
}

void
Tetrominoes::rotate(){
	
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