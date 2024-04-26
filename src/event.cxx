#include "tetris.hxx"
#include <stdlib.h>
#ifdef ON_UNIX
#include <unistd.h>
#else
#include <Windows.h>
#include <conio.h>
#endif
#include <stdio.h>

int
Tetris::key_event(){
#ifdef ON_UNIX
	return key_event_unix();
#else
	return key_event_win();
#endif
}

#ifdef ON_UNIX
int
Tetris::key_event_unix(){
	system("stty raw -echo -F /dev/tty");

	fd_set rfds;
	struct timeval tv;
	int ch = -1;

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = 10;

	while(select(1, &rfds, 0, 0, &tv) > 0)
		ch = getchar();

	//while(getchar());

	system("stty -raw echo -F /dev/tty");
	if(ch == 3) exit(0);

	switch(ch){
		case 97: tetro_slide_left(); break;
		case 100: tetro_slide_right(); break;
		case 119: tetro->rotate(); break;
		case 115: accelarate();
		default: return 0;
	}
	return 1;
}

#else

int
Tetris::key_event_win(){
	int ch = -1;
	if(_kbhit()){
		ch = _getch();
		switch(ch){
			case 97: tetro->slide_left(); break;
			case 100: tetro->slide_right(); break;
			case 119: tetro->rotate(); break;
			case 115: accelarate();
			default: return 0;
		}
		return 1;
	}
	return 0;
}
#endif