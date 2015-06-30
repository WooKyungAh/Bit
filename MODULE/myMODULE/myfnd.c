#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/signal.h>
//#include <sys/types.h>
#include <string.h>
#include <asm/ioctls.h>

#define KEY_NUM1	1
#define KEY_NUM2    2
#define KEY_NUM3    3
#define KEY_NUM4    4
#define KEY_NUM5    5
#define KEY_NUM6    6
#define KEY_NUM7    7
#define KEY_NUM8    8
#define KEY_NUM9    9
#define KEY_NUM10   10
#define KEY_NUM11   11
#define KEY_NUM12   12

#define dbg(x...)       printf(x)

#define Dev  "/dev/woo"

int  Fd = (-1);

int FNDTest(char a, char b, char c, char d){

	unsigned char FND_DATA_TBL[]={
		0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90, 0xff
	};
	unsigned char fnd_num[4];

	fnd_num[0] = FND_DATA_TBL[a];
	fnd_num[1] = FND_DATA_TBL[b];
	fnd_num[2] = FND_DATA_TBL[c];
	fnd_num[3] = FND_DATA_TBL[d];

	write(Fd, &fnd_num, sizeof(fnd_num));

	return 0;
}


unsigned char tactsw_get(int tmo)
{   
	unsigned char b;

	if (tmo) { 
		if (tmo < 0)
			tmo = ~tmo * 1000;
		else
			tmo *= 1000000;

		while (tmo > 0) {
			usleep(100000);
			read(Fd, &b, sizeof(b));
			if (b) return(b);
			tmo -= 100000;
		}
		return(-1); 
	}
	else {

		read(Fd, &b, sizeof(b));
		return(b);
	}
}

int main()
{
    unsigned char c;

    if((Fd = open( Dev, O_RDWR )) < 0){         // KEY open
		perror("open faile /dev/woo");
		exit(-1);
	}

	while(1){
		c = tactsw_get(10);
        switch (c) {
			case KEY_NUM1:  dbg("KEY_NUM1\n"); break;
			case KEY_NUM2:  dbg("KEY_NUM2\n"); break;
			case KEY_NUM3:  dbg("KEY_NUM3\n"); break;
			case KEY_NUM4:  dbg("KEY_NUM4\n"); break;
			case KEY_NUM5:  dbg("KEY_NUM5\n"); break;
			case KEY_NUM6:  dbg("KEY_NUM6\n"); break;
			case KEY_NUM7:  dbg("KEY_NUM7\n"); break;
			case KEY_NUM8:  dbg("KEY_NUM8\n"); break;
			case KEY_NUM9:  dbg("KEY_NUM9\n"); break;
			case KEY_NUM10:  dbg("KEY_NUM10\n"); break;
			case KEY_NUM11:  dbg("KEY_NUM11\n"); break;
			case KEY_NUM12:  dbg("KEY_NUM12\n"); break;
			default: /* timeout */ break;
        }
		if(c < 10)
			FNDTest(10,10,10,c);
		else
			FNDTest(10,10,1,c-10);
	}
	return 0;
}

/* EOF */
