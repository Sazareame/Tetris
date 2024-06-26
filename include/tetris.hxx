#ifndef TETRIS_HXX_
#define TETRIS_HXX_

#include "block.hxx"
#include "macros.hxx"
#include <deque>

class Tetris{
	Tetrominoes* tetro = 0;
	Tetrominoes* next = 0;

	bool game_is_over = false;
	const int default_elapse;
	int elapse;
	unsigned long score = 0;

	std::deque<uint16_t> status{};
	std::deque<uint16_t> previous{};

	void make_tetro();
	void wait()const;
	void wait(unsigned long interval)const;
	void update();
	void stop();
	int key_event();
	void accelarate();
	void show()const;
	std::deque<uint16_t>::iterator eliminate();
	bool will_overlap(int vert_pos, int hori_pos);
	void tetro_slide_right();
	void tetro_slide_left();

	void dump(int flag)const;
	void dbg_show();

	/*
	colour    falg
	red       1
	green     2
	yellow    3
	blue      4
	mage      5
	cyan      6
	white     7
	*/
	void set_colour(int flag)const;
#ifdef ON_UNIX
	int key_event_unix();
#else
	int key_event_win();
#endif

public:
	Tetris(int _default_elapse = 400): default_elapse(_default_elapse){
		elapse = default_elapse;
		status.resize(SCREEN_HEIGHT);
	}
	~Tetris(){
		if(tetro) delete tetro;
		if(next) delete next;
	}
	// drop a tetro from top to where it should stop
	void step();
	bool is_end()const;
	void start();
	void quit();
};

#endif