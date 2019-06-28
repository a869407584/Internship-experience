#include "bmp.h"


int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height)
{
	int fd_fb0;
	fd_fb0 = open("/dev/fb0", O_RDWR);
	if (fd_fb0 == -1)
	{
		printf("open /dev/fb0 fail!\n");
		return -1;
	}

	int *p_mmap = NULL;
	p_mmap = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb0, 0);
	if (p_mmap == MAP_FAILED)
	{
		printf("mmap faile!\n");
		return -1;
	}

	int *p_user = p_mmap;

	p_user = p_user + 800 * coordinate_y + coordinate_x;

	int x, y;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < wide; x++)
		{
			*(p_user + 800 * y + x) = color;
		}
	}
	close(fd_fb0);
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
char* input1()
{
	int x = 0;
	int y = 0;
	int m=0;
	char *ret = (char *)malloc(sizeof(char) * 6);
	int count =0;
	while (count<6)
	{
		read_ts(&x, &y);
		if ((x > 210 && x < 330) && (y > 215 && y < 265)) {
			// 1
			arm6818_bmp("/root/project/images/UI/1.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "1");
			count++;
			printf("1\n");
		}
		else if ((x > 340 && x < 460) && (y > 215 && y < 265)) {
			// 2
			arm6818_bmp("/root/project/images/UI/2.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "2");
			count++;
			printf("2\n");
		}
		else if ((x > 470 && x < 590) && (y > 215 && y < 265)) {
			// 3
			arm6818_bmp("/root/project/images/UI/3.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "3");
			count++;
			printf("3\n");
		}
		else if ((x > 210 && x < 330) && (y > 275 && y < 325)) {
			// 4
			arm6818_bmp("/root/project/images/UI/4.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "4");
			count++;
			printf("4\n");
		}
		else if ((x > 340 && x < 460) && (y > 275 && y < 325)) {
			// 5
			arm6818_bmp("/root/project/images/UI/5.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "5");
			count++;
			printf("5\n");
		}
		else if ((x > 470 && x < 590) && (y > 275 && y < 325)) {
			// 6
			arm6818_bmp("/root/project/images/UI/6.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "6");
			count++;
			printf("6\n");
		}
		else if ((x > 210 && x < 330) && (y > 330 && y < 380)) {
			// 7
			arm6818_bmp("/root/project/images/UI/7.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "7");
			count++;
			printf("7\n");
		}
		else if ((x > 340 && x < 460) && (y > 330 && y < 380)) {
			// 8
			arm6818_bmp("/root/project/images/UI/8.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "8");
			count++;
			printf("8\n");
		}
		else if ((x > 470 && x < 590) && (y > 330 && y < 380)) {
			// 9
			arm6818_bmp("/root/project/images/UI/9.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "9");
			count++;
			printf("9\n");
		}
		else if ((x > 340 && x < 460) && (y > 390 && y < 440)) {
			// 0
			arm6818_bmp("/root/project/images/UI/0.bmp", 280 + (m++ * 40), 110, 40, 40);
			strcat(ret, "0");
			count++;
			printf("0\n");
		}
		else if ((x > 210 && x < 330)&(y > 390 && y < 440))
		{
			printf("清除！");
			free(ret);
			while (count != 0)
			{
				arm6818_color(0x3299CC, 280 + ((count - 1) * 40), 110, 40, 40);
				count--;
			}
			m=0;
			return ret=(char*)malloc(sizeof(char)*6);
		}
		else if ((x > 470 && x < 590)&(y > 390 && y < 440))
		{
			printf("确认!");
			break;
		}
		else if (x >= 240 && x <= 600 && y >= 110 && y <= 150)
		{
			arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
			return ret;
			input1();
		}
	
		else if (x >= 240 && x <= 600 && y >= 160 && y <= 200)
		{
			return ret;
			input2();
		}
	}
	read_ts(&x, &y);
	if ((x > 210 && x < 330)&(y > 390 && y < 440))
	{
		printf("清除！");
		free(ret);
		while (count != 0)
		{
			arm6818_color(0x3299CC, 280 + ((count - 1) * 40), 110, 40, 40);
			count--;
		}
		m=0;
		return ret=(char*)malloc(sizeof(char)*6);
	}

	else if ((x > 470 && x < 590)&(y > 390 && y < 440))
	{
		printf("确认!");
		return ret;
	}
	else if (x >= 240 && x <= 600 && y >= 110 && y <= 150)
	{
		arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
		return ret;
		input1();
	}
	else if (x >= 240 && x <= 600 && y >= 160 && y <= 200)
	{
		return ret;
		input2();
	}
	return ret;
}

char* input2()
{
	int x = 0;
	int y = 0;
	int m = 0;
	char *ret=(char *)malloc(sizeof(char)*6);
	int count = 0;
	while(count<6)
	{
		read_ts(&x, &y);
		//if( x >= 240 && x <= 600 && y >= 110 && y <= 150){
		//输入账号
		//printf("账号\n");
		//}else if(x >= 240 && x <= 600 && y >= 160 && y <= 200){
		//输入密码
		//printf("password\n");
		if((x>210&&x<330)&&(y>215&&y<265)){
			// 1
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "1");
			count++;
			printf("1\n");
		}else if((x>340&&x<460)&&(y>215&&y<265)){
			// 2
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "2");
			count++;
			printf("2\n");
		}else if((x>470&&x<590)&&(y>215&&y<265)){
			// 3
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "3");
			count++;
			printf("3\n");
		}else if((x>210&&x<330)&&(y>275&&y<325)){
			// 4
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "4");
			count++;
			printf("4\n");
		}else if((x>340&&x<460)&&(y>275&&y<325)){
			// 5
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "5");
			count++;
			printf("5\n");
		}else if((x>470&&x<590)&&(y>275&&y<325)){
			// 6
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "6");
			count++;
			printf("6\n");
		}else if((x>210&&x<330)&&(y>330&&y<380)){
			// 7
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "7");
			count++;
			printf("7\n");
		}else if((x>340&&x<460)&&(y>330&&y<380)){
			// 8
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "8");
			count++;
			printf("8\n");
		}else if((x>470&&x<590)&&(y>330&&y<380)){
			// 9
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "9");
			count++;
			printf("9\n");
		}else if((x>340&&x<460)&&(y>390&&y<440)){
			// 0
			arm6818_bmp("/root/project/images/UI/yinshi.bmp",280 + (m++ * 40),160,40,40);
			strcat(ret, "0");
			count++;
			printf("0\n");
		}
		else if ((x > 210 && x < 330)&(y > 390 && y < 440))
		{
			printf("清除！");
			free(ret);
			while (count != 0)
			{
				arm6818_color(0x3299CC, 280 + ((count - 1) * 40), 160, 40, 40);
				count--;
			}
			m=0;
			return ret=(char*)malloc(sizeof(char)*6);
		}
		else if ((x > 470 && x < 590)&(y > 390 && y < 440))
		{
			printf("确认!");
			break;
		}
		else if (x >= 240 && x <= 600 && y >= 110 && y <= 150)
		{
			return ret;
			input1();
		}
		else if (x >= 240 && x <= 600 && y >= 160 && y <= 200)
		{
			arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
			m = 0;
			input2();
		}
	}
	read_ts(&x, &y);
	if ((x > 210 && x < 330)&(y > 390 && y < 440))
	{
		printf("清除！");
		while (count != 0)
		{
			arm6818_color(0x3299CC, 280 + ((count - 1) * 40), 160, 40, 40);
			count--;
		}
		m=0;
		return ret=(char*)malloc(sizeof(char)*6);
	}
	else if (x >= 240 && x <= 600 && y >= 110 && y <= 150)
	{
		return ret;
		input1();
	}
	else if (x >= 240 && x <= 600 && y >= 160 && y <= 200)
	{
		arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
		m = 0;
		input2();
	}
	else if ((x > 470 && x < 590)&(y > 390 && y < 440))
	{
		printf("确认!");
		return ret;
	}
	return ret;
}

int show_bmp800_480(char *pathname)
{
	int i;
	int ret;
	int x, y;
	int fd_bmp, fd_lcd;
	//1，打开图片，打开LCD屏幕。（open）	
	fd_bmp = open(pathname, O_RDWR);
	fd_lcd = open("/dev/fb0", O_RDWR);	
	if(fd_bmp==-1 || fd_lcd==-1)
	{
		printf("open bmp or lcd fail!\n");
		return -1;
	}
	
	//2，去掉不是像素的信息（54byte）。（lseek）
	ret = lseek(fd_bmp, 54, SEEK_SET);
	if(ret == -1)
	{
		printf("lseek bmp fail!\n");
	}
	
	//3，读取BMP图片的像素到LCD屏幕中。（read，mmap）	
	char bmp_buf[800*480*3];
	int lcd_buf[800*480];
	bzero(bmp_buf, sizeof(bmp_buf));
	bzero(lcd_buf, sizeof(lcd_buf));
	
	ret = read(fd_bmp, bmp_buf, sizeof(bmp_buf));
	if(ret == -1)
	{
		printf("read bmp fail!\n");
		return -1;		
	}
	
	//算法1：800*480BMP像素变成800*480LCD像素。
	for(i=0; i<800*480; i++)
	{
		lcd_buf[i] = bmp_buf[i*3]<<0 | bmp_buf[i*3+1]<<8 | bmp_buf[i*3+2]<<16;
		//i=0-->lcd_buf[0] = bmp_buf[0]<<0 | bmp_buf[1]<<8 | bmp_buf[2]<<16;
		//i=1-->lcd_buf[1] = bmp_buf[3]<<0 | bmp_buf[4]<<8 | bmp_buf[5]<<16;
		//i=2-->lcd_buf[2] = bmp_buf[6]<<0 | bmp_buf[7]<<8 | bmp_buf[8]<<16;
		//i=3-->lcd_buf[3] = bmp_buf[9]<<0 | bmp_buf[10]<<8 | bmp_buf[11]<<16;
	}
	
	//创建映射关系，将DDR3中的数据通过映射空间映射到显存中显示图像。
	int *lcd_mmap;
	lcd_mmap = mmap( NULL, 
				800*480*4,
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
                fd_lcd, 
				0);
	
	//算法2：解决图片颠倒问题
	for(y=0; y<480; y++)
	{
		for(x=0; x<800; x++)
		{
			*(lcd_mmap+(479-y)*800+x) = lcd_buf[y*800+x];
		}		
	}
				  
	//4，回收申请的资源给系统。（close，munmap）
	close(fd_bmp);
	close(fd_lcd);	
	munmap(lcd_mmap, 800*480*4);	
	
	return 0;
}
