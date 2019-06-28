#include<stdio.h>//printf
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close
#include <linux/input.h>//struct input_event
int lcd_input()
{
		int fd_event0;
	fd_event0 = open("/dev/input/event0", O_RDWR);
	if(fd_event0 == -1)
	{
		printf("open /dev/input/event0 fail!\n");
		return -1;
	}
	struct input_event coordinate;
	while(1)
	{		
		read(fd_event0, &coordinate,sizeof(struct input_event));
		//printf("type:%d; code:%d; value:%d\n", coordinate.type, coordinate.code, coordinate.value);			
		if(coordinate.type==3)
		{
			if(coordinate.code==0)
				printf("X=%d,",coordinate.value);
			else if(coordinate.code==1)
				printf("Y=%d\n",coordinate.value);
		}
		if(coordinate.type==1&&coordinate.code==330&&coordinate.code==0)
		{
			break;
		}
	}
	close(fd_event0);
}
int main(int argc, char *argv[])
{
	lcd_input();
	return 0;
}
