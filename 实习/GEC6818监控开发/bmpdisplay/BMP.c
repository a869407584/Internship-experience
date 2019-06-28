#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char bmpbuf[800*480*3];
	int lcdbuf[800*480];
	int tempbuf[800*480];
	
	int fd_lcd = open("/dev/fb0",O_RDWR);
	if(fd_lcd==-1)
	{
		perror("open lcd");
	}
	int fd_bmp = open("/root/project/images/625.bmp",O_RDONLY);
	if(fd_lcd==-1)
	{
		perror("open bmp");
	}
	
	lseek(fd_bmp,54,SEEK_SET);
	read(fd_bmp,bmpbuf,800*480*3);
	
	int i,j;
	for(i = 0; i < 800*480; i++)
	{
	lcdbuf[i] = bmpbuf[i*3+0] << 0 | bmpbuf[i*3+1] << 8 | bmpbuf[i*3+2] << 16 | 0x00 << 24;
	}
	for(i = 0; i < 800; i++)
		for(j = 0; j < 480; j++)
		{
			tempbuf[(479-j)*800+i] = lcdbuf[j*800+i];
		}
	write(fd_lcd,tempbuf,800*480*4);
	
	close(fd_bmp);
	close(fd_lcd);
	return 0;
}
