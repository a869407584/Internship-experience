#include<stdio.h>//printf
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close
#include <sys/mman.h>//mmap¡¢munmap

int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height)
{
	int fd_fb0;
	fd_fb0 = open("/dev/fb0", O_RDWR);
	if(fd_fb0 == -1)
	{
		printf("open /dev/fb0 fail!\n");
		return -1;
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
			*(p_user + 800*y + x) = color;
		}
	}
	
	close(fd_fb0);	
	
	return 0;
}

int main(int argc, char *argv[])
{
	arm6818_color(0x00ff0000, 10, 10, 100, 100);
	return 0;
}