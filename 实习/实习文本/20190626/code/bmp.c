#include<stdio.h>//printf
#include <sys/types.h>//open\lseek
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close\lseek
#include <sys/mman.h>//mmap¡¢munmap
#include <strings.h>//bzero

int arm6818_bmp(const char *pathname, int coordinate_x, int coordinate_y, int wide, int height)
{
	int fd_fb0;
	fd_fb0 = open("/dev/fb0", O_RDWR);
	if(fd_fb0 == -1)
	{
		printf("open /dev/fb0 fail!\n");
		return -1;
	}
	
	int fd_bmp;
	fd_bmp = open(pathname, O_RDWR);
	if(fd_bmp == -1)
	{
		printf("open bmp fail!\n");
		return -1;
	}
	
	char bmp_buf[800*480*3];
	int lcd_buf[800*480];
	bzero(bmp_buf, sizeof(bmp_buf));
	bzero(lcd_buf, sizeof(lcd_buf));
	
	lseek(fd_bmp, 54, SEEK_SET);
	read(fd_bmp, bmp_buf, sizeof(bmp_buf));
	
	int i;
	char A = 0x00;
	for(i=0; i<800*480; i++)
	{
		lcd_buf[i] = bmp_buf[i*3]<<0 | bmp_buf[i*3+1]<<8 | bmp_buf[i*3+2]<<16 | A<<24;
	}

	int *p_mmap = NULL;
	p_mmap = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE , MAP_SHARED, fd_fb0, 0);
	if(p_mmap == MAP_FAILED)
	{
		printf("mmap faile!\n");
		return -1;		
	}
	
	int *p_user = p_mmap;
	
	p_user = p_user + 800*coordinate_y + coordinate_x;

	int x, y;
	for(y=0; y<height; y++)
	{
		for(x=0; x<wide; x++)
		{
			*(p_user + (height-1-y)*800 + x) = lcd_buf[wide*y+x];
		}
	}
	
	close(fd_fb0);	
	return 0;
}

int main(int argc, char *argv[])
{
	arm6818_bmp("/root/project/images/2.bmp", 0, 0, 800, 480);
	return 0;
}

