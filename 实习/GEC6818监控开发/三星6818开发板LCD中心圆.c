#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <linux/input.h>
int main()
{
	char *pathName = "/dev/fb0";
	int x=400;
	int y=240;
	int r=50;
	int x1=0;
	int y1=0;
	int xbiaozhi=1;
	int ybiaozhi=1;
	unsigned int *p_mmap;
	int *temp = NULL;
	int fd_fb0 = open(pathName, O_RDWR);
	p_mmap = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb0, 0);
	int i=0;
	while(1)
	{
		for(y1=0;y1<480;y1++)
		{
			for(x1=0;x1<800;x1++)
			{
				i=pow(x1-x,2)+pow(y1-y,2);
				if((i<=r*r))
				{
					*(p_mmap+800*y1+x1)=0x0000f00;
				}
				else
				{
					*(p_mmap+800*y1+x1)=0x00000000;
				}
			}
		}
		if((y+r)>479)
		{
			ybiaozhi=2;
		}
		if((x+r)>799)
		{
			xbiaozhi=2;
		}
		if((y-r)<0)
		{
			ybiaozhi=1;
		}
		if((x-r)<0)
		{
			xbiaozhi=1;
		}
		if(xbiaozhi==1)
		{
			x++;
		}
		if(xbiaozhi==2)
		{
			x--;
		}
		if(ybiaozhi==1)
		{
			y++;
		}
		if(xbiaozhi==2)
		{
			y--;
		}
	}
	munmap(p_mmap,800*480*4);
	close(fd_fb0);
	return 0;
}