#include<stdio.h>
#include<pthread.h>
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close\sleep
#include <sys/mman.h>//mmap、munmap
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
void *1_id(void *arg)
{
	while(1)
	{
		arm6818_color(00ff0000,0,0,400,240);usleep(10000);
		arm6818_color(0000ff00,0,0,400,240);usleep(10000);
		arm6818_color(000000ff,0,0,400,240);usleep(10000);
	}
}
void *2_id(void *arg)
{
	while(1)
	{
		arm6818_color(00ff0000,400,0,400,240);usleep(100000);
		arm6818_color(0000ff00,400,0,400,240);usleep(100000);
		arm6818_color(000000ff,400,0,400,240);usleep(100000);
	}
}
void *3_id(void *arg)
{
	while(1)
	{
		arm6818_color(00ff0000,0,240,400,240);sleep(1);
		arm6818_color(0000ff00,0,240,400,240);sleep(1);
		arm6818_color(000000ff,0,240,400,240);sleep(1);
	}
}
void *4_id(void *arg)
{
	while(1)
	{
		arm6818_color(00ff0000,400,240,400,240);sleep(2);
		arm6818_color(0000ff00,400,240,400,240);sleep(2);
		arm6818_color(000000ff,400,240,400,240);sleep(2);
	}
}
int main(int argc,char *argv[])
{
	pthread_t 1_id;
	pthread_t 2_id;
	pthread_t 3_id;
	pthread_t 4_id;
	pthread_create(1_id;,NULL,1_id,NULL);
	pthread_create(2_id,NULL,2_id,NULL);
	pthread_create(3_id,NULL,3_id,NULL);
	pthread_create(4_id,NULL,4_id,NULL);
	pthread_join(1_id, NULL);
	pthread_join(1_id, NULL);
	pthread_join(1_id, NULL);
	pthread_join(1_id, NULL);
	return 0;
}