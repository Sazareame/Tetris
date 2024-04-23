#include <stdio.h>
#include <stdlib.h>

#define TTY_PATH "/dev/tty"
#define STTY_US "stty raw -echo -F"
#define STTY_DEF "stty -raw echo -F"

int
get_char(){
	fd_set rfds;
	struct timeval tv;
	int ch = 0;

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	tv.tv_sec = 0;
	tv.tv_usec = 10;

	if(select(1, &rfds, 0, 0, &tv) > 0){
		ch = getchar();
	}
	return ch;
}

signed main(){
	int ch = 0;
	system(STTY_US TTY_PATH);
	for(;;){
		ch = get_char();
		if(ch){
			printf("%d\n\r", ch);
		}
		if(ch == 3){
			system(STTY_DEF TTY_PATH);
			return 0;
		}
	}
}