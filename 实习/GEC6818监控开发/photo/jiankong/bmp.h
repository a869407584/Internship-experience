#ifndef _BMP_H
#define _BMP_H

#include <stdio.h>//printf
#include <sys/types.h>//open,lseek
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <strings.h>//bzero
#include <unistd.h>//lseek,read
#include <sys/mman.h>//mmap,munmap
#include <linux/input.h>
#include<string.h>
#include <malloc.h>
#include "font.h"
extern int show_bmp800_480(char *pathname);
int arm6818_bmp(const char *pathname, int coordinate_x, int coordinate_y, int wide, int height);
int arm6818_color(int color, int coordinate_x, int coordinate_y, int wide, int height);
int fd_event0;
char* input1();
char* input2();
#endif