#include<stdio.h>
#include <pthread.h>
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close\sleep
#include <sys/mman.h>//mmap、munmap
int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height);

int fd_fb0;
void *task1(void *arg)
{
	while(1)
	{
		arm6818_color(0x00ff0000,0,0,400,240);usleep(10*1000);
		arm6818_color(0x0000ff00,0,0,400,240);usleep(10*1000);
		arm6818_color(0x000000ff,0,0,400,240);usleep(10*1000);
	}
	pthread_exit(NULL);
}
void *task2(void *arg)
{
	while(1)
	{
		arm6818_color(0x00ff0000,400,0,400,240);usleep(100*1000);
		arm6818_color(0x0000ff00,400,0,400,240);usleep(100*1000);
		arm6818_color(0x000000ff,400,0,400,240);usleep(100*1000);
	}
	pthread_exit(NULL);
}
void *task3(void *arg)
{
	while(1)
	{
		arm6818_color(0x00ff0000,0,240,400,240);sleep(1);
		arm6818_color(0x0000ff00,0,240,400,240);sleep(1);
		arm6818_color(0x000000ff,0,240,400,240);sleep(1);
	}
	pthread_exit(NULL);
}
void *task4(void *arg)
{
	while(1)
	{
		arm6818_color(0x00ff0000,400,240,400,240);sleep(2);
		arm6818_color(0x0000ff00,400,240,400,240);sleep(2);
		arm6818_color(0x000000ff,400,240,400,240);sleep(2);
	}
	pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
	pthread_t id1,id2,id3,id4;
	pthread_create(&id1,NULL,task1,NULL);
	pthread_create(&id2,NULL,task2,NULL);
	pthread_create(&id3,NULL,task3,NULL);
	pthread_create(&id4,NULL,task4,NULL);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);
	return 0;
}
int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height)
{
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
	munmap(p_mmap,800*480*4);
	p_user=NULL;
	return 0;
}