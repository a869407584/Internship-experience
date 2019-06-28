
#include "bmp.h"
#include "touch_screen.h"
#include "camera.h"

int main(int argc, char *argv[])
{
	int x = 0;
	int y = 0;
	int m = 0;
	int n = 1;
	int count = 2;
	arm6818_bmp("/root/project/images/UI/625.bmp", 0, 0, 800, 480);
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
			//ÊäÈëÕËºÅ
			printf("ÕËºÅ£º\n");
			account=input1();
			printf("ÕËºÅÊÇ:%s", account);
			printf("\n");
		}
		else if(x >= 240 && x <= 600 && y >= 160 && y <= 200)
		{
			//ÊäÈëÃÜÂë
			printf("ÃÜÂë£º\n");
			password=input2();
			printf("ÃÜÂëÊÇ:%s", password);
			printf("\n");
		}
		else if ((x > 470 && x < 590)&(y > 390 && y < 440))
		{
			if (strcmp(account, account_real) == 0 && (strcmp(password, password_real) == 0))
			{
				printf("ÊäÈëÕýÈ·!");
				arm6818_color(0x0000ff00, 0, 0, 800, 480); sleep(1);
	
	            show_bmp800_480("/root/project/images/2.bmp");
	            my_camera();
			}
			else
			{
				printf("ÊäÈë´íÎó!");
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
	return 0;
}

