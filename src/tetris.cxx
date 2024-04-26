#include "tetris.hxx"
#include <random>
#include <chrono>
#include <fstream>
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
	if(!next){
		int new_index = d(e);
		tetro = new Tetrominoes(new_index);
	}else{
		tetro = next;
	}
	next = new Tetrominoes(index);
}

void
Tetris::step(){
	make_tetro();
	previous = status;
	elapse = default_elapse;
	auto start_timestamp = std::chrono::system_clock::now();
	for(;;){
		auto time_elapsed = std::chrono::system_clock::now();
		if(key_event()){
			update();
#ifdef DBG_MODE
			dump(1);
#endif
			show();
			status = previous;
			continue;
		}else{
			wait();
		}
		if(std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed - start_timestamp).count() > elapse){
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
			start_timestamp = std::chrono::system_clock::now();
			update();
#ifdef DBG_MODE
			dump(0);
#endif
			show();
			status = previous;
		}
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
	elapse = 1;
}

void
Tetris::show()const{
	MAKE_BOLD;
	CLEAR_SCREEN;
	START_DRAW;
	DRAW_BOUNDARY_LINE;
	printf("       your score: %lu\n", score);
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
			PUTWALL;
			DRAW_NEXT_LINE;
		}
	}
	DRAW_BOUNDARY_LINE;

	if(next){
	START_NEXT_HINT;
	printf("Next Tetro:");
	HINT_DOWN;
	HINT_DOWN;
	uint16_t next_status = next->get_status();
	for(uint16_t mask = 0xf000; mask > 0; mask >>= 4){
		for(uint16_t i = (0x8888 & mask); (i & mask) != 0; i >>= 1){
			set_colour(next->get_colour());
			if(i & (next_status & mask))
				PUTBLOCK;
			else
			 	PUTSPACE;
		}
		HINT_DOWN;
	}
	}
	RESET_ALL;
	MOVE_CURSOR;
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

void
Tetris::dump(int flag)const{
	auto f = std::fstream("./debug_info.txt", std::fstream::app);
	if(!f.is_open()) exit(0);
	switch(flag){
	case 1:
		f << "\ntriggered by movement\n";
		break;
	case 0:
	 	f << "\ntriggerd by dropping\n";
		break;
	case 2:
		f << "\nrecored after sleep\n";
		break;
	}
	f << "horizen position: " << tetro->get_hori_pos() << "\n";
	f << "vertical position: " << tetro->get_vert_pos() << "\n";
	f << "tetro status" << tetro->get_status() << "\n";
	f << "game status:\n\t";
	for(auto const& line: status)
		f << line << "\n\t";
}

void
Tetris::dbg_show(){
	CLEAR_SCREEN;
	printf("movement occured\n");
	fflush(stdout);
}