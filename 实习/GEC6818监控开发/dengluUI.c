#include <stdio.h>
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//close
#include <sys/mman.h>//mmap、munmap
#include <string.h>
#include <linux/input.h>


int arm6818_bmp(const char *pathname, int coordinate_x, int coordinate_y, int wide, int height);
int read_ts(int *coordinate_x, int *coordinate_y);
int close_ts(void);
int open_ts(void);
int read_ts(int *coordinate_x, int *coordinate_y);
int fd_event0;


int main(int argc,char *argv[])
{
	int x=0,y=0;
	arm6818_bmp("/root/project/images/625.bmp", 0, 0, 800, 480);
	open_ts();

	while(1)
	{
		read_ts(&x,&y);
		if((x>210&&x<330)&&(y>215&&y<265))
			arm6818_bmp("./1.bmp",280,110,40,40);
		else if((x>340&&x<460)&&(y>215&&y<265))
			arm6818_bmp("./2.bmp",320,110,40,40);
		else if((x>470&&x<590)&&(y>215&&y<265))
			arm6818_bmp("./3.bmp",360,110,40,40);
		else if((x>210&&x<330)&&(y>275&&y<325))
			arm6818_bmp("./4.bmp",400,110,40,40);
		else if((x>340&&x<460)&&(y>275&&y<325))
			arm6818_bmp("./5.bmp",440,110,40,40);
		else if((x>470&&x<590)&&(y>275&&y<325))
			arm6818_bmp("./6.bmp",480,110,40,40);
		else if((x>210&&x<330)&&(y>330&&y<380))
			arm6818_bmp("./7.bmp",520,110,40,40);
		else if((x>340&&x<460)&&(y>330&&y<380))
			arm6818_bmp("./8.bmp",560,110,40,40);
		else if((x>470&&x<590)&&(y>330&&y<380))
			arm6818_bmp("./9.bmp",600,110,40,40);
		else if((x>210&&x<330)&&(y>390&&y<440))
			printf("清除\n");
		else if((x>340&&x<460)&&(y>390&&y<440))
			arm6818_bmp("./0.bmp",640,110,40,40);
		else if((x>470&&x<590)&&(y>390&&y<440))
			printf("确定\n");
		else 
			printf("kongbai\n");
		
	}
	close_ts();
	
	return 0;
}


int open_ts(void)
{
	fd_event0 = open("/dev/input/event0", O_RDWR);
	if(fd_event0 == -1)
	{
		printf("open /dev/input/event0 fail!\n");
		return -1;
	}	
	return 0;
}

int read_ts(int *coordinate_x, int *coordinate_y)
{
	struct input_event coordinate;
	while(1)
	{		
		read(fd_event0, &coordinate,sizeof(struct input_event));
		//printf("type:%d; code:%d; value:%d\n", coordinate.type, coordinate.code, coordinate.value);	
		//type:3; code:0; value:550
		//type:3; code:1; value:184
		//type:1; code:330; value:0
		if(coordinate.type==3 && coordinate.code==0 && coordinate.value>=0 && coordinate.value<800)//X
		{
			*coordinate_x = coordinate.value;
		}
		if(coordinate.type==3 && coordinate.code==1 && coordinate.value>=0 && coordinate.value<480)//Y
		{
			*coordinate_y = coordinate.value;
		}		
		if(coordinate.type==1 && coordinate.code==330 && coordinate.value==0)
		{
			break;
		}	
	}	
	
	
	return 0;
}
int close_ts(void)
{
	close(fd_event0);	
	
	return 0;
}
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




