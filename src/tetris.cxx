#include "tetris.hxx"
#include <random>
#include <chrono>
#ifdef ON_UNIX
#include <unistd.h>
#else
#include <Windows.h>
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
	elapse = 600;
	auto start_timestamp = std::chrono::system_clock::now();
	for(;;){
		wait();
		auto time_elapsed = std::chrono::system_clock::now();
		if(std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed - start_timestamp).count() > 600){
			start_timestamp = time_elapsed;	
			goto exedrop;
		}
		if(key_event()){
			update();
			show();
			status = previous;
			continue;
		}
exedrop:
		int cmp_line = tetro->get_vert_pos() + 1;
		int offset = tetro->get_hori_pos();
		// get the bottom
		if(cmp_line == 20){
			stop();
			return;
		}
		// overlapped
		if(will_overlap(cmp_line, offset)){
			stop();
			return;
		}
		tetro->drop();
		update();
		show();
		status = previous;
	}
}

bool
Tetris::will_overlap(int vert_pos, int hori_pos){
	if(hori_pos < 0 || hori_pos > SCREEN_WIDTH)
		return false;
	uint16_t tetro_status = tetro->get_status();
	for(int i = 0; i < 4; i++){
		if(vert_pos - i < 0) break;
		if(((status[vert_pos - i] >> hori_pos) & 0x000f) & tetro_status){
			return true;
		}
		tetro_status >>= 4;
	}
	return false;
}

void
Tetris::wait()const{
	wait(elapse);
}

void
Tetris::wait(unsigned long interval)const{
#ifdef ON_UNIX
	usleep(interval * 1000);
#else
	Sleep(interval);
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
	elapse = 2;
}

void
Tetris::show()const{
	MAKE_BOLD;
	CLEAR_SCREEN;
	START_DRAW;
	DRAW_BOUNDARY_LINE;
	printf("    your score: %lu\n", score);
	auto pre = previous.cbegin();
	for(auto cur = status.cbegin(); cur != status.cend(); ++cur, ++pre){
		PUTWALL;
		if((*cur & 0x03ff) == 0){
			DRAW_ONE_LINE_SPACE;
			PUTWALL;
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
			PUTWALL;
			DRAW_NEXT_LINE;
		}
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
		wait(500);
		CLEAR_SCREEN;
		fflush(stdout);
		wait(100);
	}
	RESET_ALL;
}

void
Tetris::quit(){
	MAKE_BOLD;
	CLEAR_SCREEN;
	printf("\n\n\n\n\t\tGame Over!\n\n\t\tYour Score: %lu\n\n\t\tThanks for Playing!", score);
	fflush(stdout);
	wait(1000);
	RESET_ALL;
}

void
Tetris::set_colour(int flag)const{
	printf("\x1b[3%dm", flag);
	printf("\x1b[4%dm", flag);
}

void
Tetris::tetro_slide_left(){
	if(will_overlap(tetro->get_vert_pos(), tetro->get_hori_pos() + 1))
		return;
	tetro->slide_left();
}

void
Tetris::tetro_slide_right(){
	if(will_overlap(tetro->get_vert_pos(), tetro->get_hori_pos() - 1))
		return;
	tetro->slide_right();
}