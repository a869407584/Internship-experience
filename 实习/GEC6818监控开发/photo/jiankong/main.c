#include "bmp.h"
#include "touch_screen.h"
#include "camera.h"
void* show_time()
{
	
	time_t t;
	char* str;
	Init_Font();
	while(1)
	{
		//清空显示区域
		Clean_Area(300,//x坐标起始点
					448,//y坐标起始点
					220,//绘制的宽度
					25,//绘制的高度	
					0x3299CC); //往屏幕指定区域填充蓝颜色
		time(&t);
		str = ctime(&t);
		Display_characterX(300,//x坐标起始点
							448,//y坐标起始点
							str,//GB2312中文字符串
							0x0000ff00,//红字体颜色值
							1);//字体放大倍数 1~8
		sleep(1);
	
	}
	UnInit_Font();
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	pthread_t time1;
	int x = 0;
	int y = 0;
	int m = 0;
	int n = 1;
	int count = 2;
	arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
	pthread_create(&time1,NULL,show_time,NULL);
	char *account = NULL;
	char *password = NULL;
	char *account_real = "123456";
	char *password_real = "123456";
	open_ts();
	while (1)
	{
		read_ts(&x,&y);
		if( x >= 240 && x <= 600 && y >= 110 && y <= 150)
		{
			//输入账号
			printf("账号：\n");
			account=input1();
			printf("账号是:%s", account);
			printf("\n");
		}
		else if(x >= 240 && x <= 600 && y >= 160 && y <= 200)
		{
			//输入密码
			printf("密码：\n");
			password=input2();
			printf("密码是:%s", password);
			printf("\n");
		}
		else if ((x > 470 && x < 590)&(y > 390 && y < 440))
		{
			if (strcmp(account, account_real) == 0 && (strcmp(password, password_real) == 0))
			{
				printf("输入正确!");
				arm6818_color(0x0000ff00, 0, 0, 800, 480); sleep(1);
				myvedio();
				break;
				
			}
			else
			{
				printf("输入错误!");
				if (count-- == 0)
				{
					arm6818_color(0x00000000, 0, 0, 800, 480);
					break;
				}
				else
				{
					arm6818_color(0x00ff0000, 0, 0, 800, 480); sleep(1);
					arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
				}
			
			}
		}
	}
	close_ts();
	pthread_join(time1,NULL);
	return 0;
}

