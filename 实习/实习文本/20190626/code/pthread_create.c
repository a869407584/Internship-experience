#include <stdio.h>//printf
#include <pthread.h>//pthread_create
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close\sleep
#include <sys/mman.h>//mmap、munmap

int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height);

void *task_ser(void *arg)
{
	while(1)
	{
	//在X:400~800;Y:0~480区域内，每隔1秒按照BRG顺序在指定的区域内填充颜色。
		arm6818_color(0x000000ff, 400, 0, 400, 480);sleep(1);		
		arm6818_color(0x00ff0000, 400, 0, 400, 480);sleep(1);
		arm6818_color(0x0000ff00, 400, 0, 400, 480);sleep(1);
	}
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t task_id;
	pthread_create(&task_id, NULL, task_ser, NULL);
	
	while(1)
	{
	//在X:0~400;Y:0~480区域内，每隔1秒按照RGB顺序在指定的区域内填充颜色。	
		arm6818_color(0x00ff0000, 0, 0, 400, 480);sleep(1);
		arm6818_color(0x0000ff00, 0, 0, 400, 480);sleep(1);
		arm6818_color(0x000000ff, 0, 0, 400, 480);sleep(1);
	}
	
	pthread_join(task_id, NULL);
	return 0;
}

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
