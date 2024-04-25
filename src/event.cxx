#include "tetris.hxx"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int
Tetris::key_event(){
	system("stty raw -echo -F /dev/tty");

	fd_set rfds;
	struct timeval tv;
	int ch = -1;

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = 50;

	if(select(1, &rfds, 0, 0, &tv) > 0)
		ch = getchar();

	system("stty -raw echo -F /dev/tty");
	if(ch == 3) exit(0);

	switch(ch){
		case 97: tetro->slide_left(); break;
		case 100: tetro->slide_right(); break;
		case 119: tetro->rotate(); break;
		case 115: accelarate();
		default: return 0;
	}
	return 1;
}