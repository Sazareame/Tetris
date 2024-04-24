#ifndef TETRIS_HXX_
#define TETRIS_HXX_

#include "screen.hxx"
#include "block.hxx"
#include <stack>

class Tetris{
	Screen screen;
	Tetrominoes* tetro = 0;

	bool game_is_over = false;

	std::stack<int> events{};
	std::deque<uint16_t> status{};

	void make_tetro(int);
	void wait()const;
	void update();
	void stop();
	void key_event();

public:
	Tetris(){
		status.resize(SCREEN_HEIGHT);
		//system("stty raw -echo -F /dev/tty");
	}
	void start();
	// drop a tetro from top to where it should stop
	void step(int);
	bool is_end()const;
	std::deque<uint16_t>::iterator eliminate();
};
















#endif