#include <stdio.h>//printf、scanf
#include "font.h"
#include <time.h>
#include <unistd.h>
#include <string.h>

/*
	int argc:终端命令行参数的个数
	const char *argv[]：终端命令行参数的内容
*/
int main(int argc, const char *argv[])
{
	Init_Font();
		
	//清空显示区域
	Clean_Area(300,//x坐标起始点
			20,//y坐标起始点
			400,//绘制的宽度
			32,//绘制的高度	
			0x000000FF); //往屏幕指定区域填充蓝颜色
	
	Display_characterX(300,//x坐标起始点
					   20,//y坐标起始点
					   "000-张三-李四",//GB2312中文字符串
					   0x00FF0000,//红字体颜色值
					   2);//字体放大倍数 1~8
	
	UnInit_Font();
	return 0;
}