#include "tetris.hxx"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

void
Tetris::key_event(){
	int fd = open("/dev/tty", O_RDONLY);
	if(fd == -1){
		printf("open error\n");
		exit(1);
	}

	fd_set rfds;

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 800000;

	struct input_event event;
	for(;;){
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		if(select(fd + 1, &rfds, 0, 0, &tv) == 1){
			if(read(fd, &event, sizeof(event))){
				if(event.type == EV_KEY && event.value == 0){
					switch(event.code){
						case 38:
						case 113: tetro->slide_left(); break;
						case 40:
						case 114: tetro->slide_right(); break;
						case 25:
						case 111: tetro->rotate(); break;
						case 39:
						case 116:
						default: break;
					}
				}
			}
		}else{
			break;
		}
	}
	close(fd);
}