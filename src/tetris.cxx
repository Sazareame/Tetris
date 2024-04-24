#include "tetris.hxx"
#include "block_type.hxx"

#include <unistd.h>
#ifdef ON_UNIX
#include <unistd.h>
#endif

void
Tetris::start(){
	screen.flush();
}

void
Tetris::make_tetro(int a){
	if(tetro) delete tetro;
	tetro = new Tetrominoes(tetros[2], a);
}

void
Tetris::step(int a){
	make_tetro(a);
	auto previous = status;
	for(;;){
		wait();
		key_event();
		uint16_t tetro_status_per_line = tetro->get_status() & 0x03ff;
		int cmp_line = tetro->get_vert_pos() + 1;
		int offset = tetro->get_hori_pos();
		// get the bottom
		if(cmp_line == 20){
			stop();
			return;
		}
		// overlapped
		for(int i = 0; i < 4; i++){
			if(cmp_line - i < 0) break;
			if(((status[cmp_line - i] >> offset) & 0x000f) & tetro_status_per_line){
				stop();
				return;
			}
			tetro_status_per_line >>= 4;
		}
		tetro->drop();
		update();
		screen.show(status);
		status = previous;
	}
}

void
Tetris::wait()const{
	usleep(600000);
#ifdef ON_UNIX
	sleep(1);
#endif
}

void
Tetris::update(){
	int tetro_bottom = tetro->get_vert_pos();
	int offset = tetro->get_hori_pos();
	uint16_t tetro_status_per_line = tetro->get_status() & 0x03ff;
	for(int i = 0; i < 4 && tetro_bottom - i >= 0; i++){
		status[tetro_bottom - i] |= ((tetro_status_per_line & 0x000f) << offset);
		tetro_status_per_line >>= 4;
	}
}

std::deque<uint16_t>::iterator
Tetris::eliminate(){
	for(auto i = status.begin(); i != status.end(); ++i){
		if((*i & 0x03ff) == 0x03ff){
			return i;
		}
	}
	return status.end();
}

bool
Tetris::is_end()const{
	return game_is_over;
}

void
Tetris::stop(){
	update();
	screen.show(status);
	auto to_be_eliminate = eliminate();
	while(to_be_eliminate != status.end()){
		status.erase(to_be_eliminate);
		status.push_front(0x0000);
	}
	if(*status.begin() == 0x03ff) game_is_over = true;
}