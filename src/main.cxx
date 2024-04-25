#include "tetris.hxx"

signed main(){
	//system("stty raw -echo -F /dev/tty");
	Tetris game{};
	// game.start();
	for(;;){
		game.step();
		if(game.is_end()){
			game.quit();
			break;
		}
	}
	return 0;
}