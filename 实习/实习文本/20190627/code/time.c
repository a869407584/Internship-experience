#include <stdio.h>//printf
#include <time.h>//time/ctime
#include <string.h>//strtok

int main(int argc, char *argvp[])
{
	time_t get_time;
	time(&get_time);
	
	printf("sizeof(time_t)=%d\n", sizeof(time_t));
	printf("gettime=%d\n", get_time);
	
	char *p_time = NULL;
	p_time = ctime(&get_time);
	
	printf("Time: %s\n", p_time);

	char *p_str_first = NULL;
	char *p_str_sec = NULL;
	
	//"Wed Jun 26 18:27:48 2019"
	p_str_first = strtok(p_time, " ");
	printf("Wed= %s\n", p_str_first);
	
	p_str_sec = strtok(NULL, " ");
	printf("Jun= %s\n", p_str_sec);
	
	int string_int;
	string_int = atoi("27");
	printf("%d\n", string_int);
	
	return 0;
}