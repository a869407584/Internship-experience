#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
int main()
{
	char *pathName = "/dev/fb0";
	int *p_mmap = NULL;
	int *temp = NULL;
	int color = 0x00000000;
	int fd_fb0 = open(pathName, O_RDWR);
	if (fd_fb0<0)
	{
		printf("open failed!");
		return -1;
	}
	p_mmap = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb0, 0);
	temp = p_mmap;
	if (p_mmap==MAP_FAILED)
	{
		printf("mmap failed!");
		return -2;
	}
	for (int i=0;i<800*480;i++)
	{
		*temp = color;
		temp++;
	}
	munmap(p_mmap, 800 * 480 * 4);
	return 0;
}
