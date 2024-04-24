#include "tetris.hxx"
#define ON_UNIX

signed main(){
	//system("stty raw -echo -F /dev/tty");
	Tetris game{};
	//game.start();
		game.step(5);
		game.step(3);
}