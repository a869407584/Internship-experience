#include <stdio.h>//printf��scanf
#include "font.h"
#include <time.h>
#include <unistd.h>
#include <string.h>

/*
	int argc:�ն������в����ĸ���
	const char *argv[]���ն������в���������
*/
int main(int argc, const char *argv[])
{
	Init_Font();
		
	//�����ʾ����
	Clean_Area(300,//x������ʼ��
			20,//y������ʼ��
			400,//���ƵĿ��
			32,//���Ƶĸ߶�	
			0x000000FF); //����Ļָ�������������ɫ
	
	Display_characterX(300,//x������ʼ��
					   20,//y������ʼ��
					   "000-����-����",//GB2312�����ַ���
					   0x00FF0000,//��������ɫֵ
					   2);//����Ŵ��� 1~8
	
	UnInit_Font();
	return 0;
}