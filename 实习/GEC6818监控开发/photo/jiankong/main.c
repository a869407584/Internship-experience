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
		//�����ʾ����
		Clean_Area(300,//x������ʼ��
					448,//y������ʼ��
					220,//���ƵĿ��
					25,//���Ƶĸ߶�	
					0x3299CC); //����Ļָ�������������ɫ
		time(&t);
		str = ctime(&t);
		Display_characterX(300,//x������ʼ��
							448,//y������ʼ��
							str,//GB2312�����ַ���
							0x0000ff00,//��������ɫֵ
							1);//����Ŵ��� 1~8
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
			//�����˺�
			printf("�˺ţ�\n");
			account=input1();
			printf("�˺���:%s", account);
			printf("\n");
		}
		else if(x >= 240 && x <= 600 && y >= 160 && y <= 200)
		{
			//��������
			printf("���룺\n");
			password=input2();
			printf("������:%s", password);
			printf("\n");
		}
		else if ((x > 470 && x < 590)&(y > 390 && y < 440))
		{
			if (strcmp(account, account_real) == 0 && (strcmp(password, password_real) == 0))
			{
				printf("������ȷ!");
				arm6818_color(0x0000ff00, 0, 0, 800, 480); sleep(1);
				myvedio();
				break;
				
			}
			else
			{
				printf("�������!");
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

