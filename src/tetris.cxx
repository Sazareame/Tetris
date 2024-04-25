#include "tetris.hxx"
#include <random>
#include <unistd.h>
#ifdef ON_UNIX
#include <unistd.h>
#endif

void
Tetris::make_tetro(){
	if(tetro) delete tetro;
	static std::mt19937_64 e(time(0));
	static std::uniform_int_distribution<> d(0, 6);
	int index = d(e);
	tetro = new Tetrominoes(index);
}

void
Tetris::step(){
	make_tetro();
	previous = status;
	elapse = 600000;
	for(;;){
		wait();
		key_event();
		uint16_t tetro_status_per_line = tetro->get_status();
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
		show();
		status = previous;
	}
}

void
Tetris::wait()const{
	usleep(elapse);
#ifdef ON_UNIX
	sleep(1);
#endif
}

void
Tetris::update(){
	int tetro_bottom = tetro->get_vert_pos();
	int offset = tetro->get_hori_pos();
	uint16_t tetro_status_per_line = tetro->get_status();
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
	show();
	auto to_be_eliminate = eliminate();
	while(to_be_eliminate != status.end()){
		status.erase(to_be_eliminate);
		score += 100;
		status.push_front(0x0000);
		to_be_eliminate = eliminate();
	}
	if(*status.begin() != 0x0) game_is_over = true;
}

void
Tetris::accelarate(){
	elapse = 60;
}

void
Tetris::show()const{
	MAKE_BOLD;
	CLEAR_SCREEN;
	fflush(stdout);
	START_DRAW;
	fflush(stdout);
	DRAW_BOUNDARY_LINE;
	printf("    your score: %lu\n", score);
	auto pre = previous.cbegin();
	for(auto cur = status.cbegin(); cur != status.cend(); ++cur, ++pre){
		putchar('+');
		if((*cur & 0x03ff) == 0){
			DRAW_ONE_LINE_SPACE;
			putchar('+');
			DRAW_NEXT_LINE;
		}
		else{
			for(uint16_t i = 0x0200; i > 0; i >>= 1){
				if(i & *pre)
					set_colour(7);
				else
					set_colour(tetro->get_colour());
				if(i & *cur)
					PUTBLOCK;
				else
					PUTSPACE;
			}
			RESET_ALL;
			putchar('+');
			DRAW_NEXT_LINE;
		}
		fflush(stdout);
	}
	DRAW_BOUNDARY_LINE;
	fflush(stdout);
}

void
Tetris::start(){
	MAKE_BOLD;
	for(int i = 0; i < 3; ++i){
		CLEAR_SCREEN;
		START_DRAW;
		printf("\n\n\n\n\t\tTetrisxx\n\n\t\tAuthor: Sazareame\n\n\t\tAll Rights Reserved");
		fflush(stdout);
		usleep(500000);
		CLEAR_SCREEN;
		fflush(stdout);
		usleep(100000);
	}
	RESET_ALL;
}

void
Tetris::quit(){
	MAKE_BOLD;
	CLEAR_SCREEN;
	printf("\n\n\n\n\t\tGame Over!\n\n\t\tYour Score: %lu\n\n\t\tThanks for Playing!", score);
	fflush(stdout);
	sleep(1);
	RESET_ALL;
}

void
Tetris::set_colour(int flag)const{
	printf("\x1b[3%dm", flag);
	printf("\x1b[4%dm", flag);
}
