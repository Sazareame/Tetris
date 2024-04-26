#include "tetris.hxx"

signed main(int argc, char const** argv){
	//system("stty raw -echo -F /dev/tty");
	Tetris game{};
	game.start();
	for(;;){
		game.step();
		if(game.is_end()){
			game.quit();
			break;
		}
	}
	return 0;
}