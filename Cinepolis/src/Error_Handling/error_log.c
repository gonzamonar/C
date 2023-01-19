
#include "error_log.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void ErrorLog_createFolder();
static void GetCurrentDateTime(char* dest);


void ErrorLog_write(char* log)
{
	char file_path[512];
	char errorTime[128];
	char errorLog[1024];

	getcwd(file_path, 512);
	strcat(file_path, "\\errorlog.txt");
	GetCurrentDateTime(errorTime);
	sprintf(errorLog, "%s | %s\n", errorTime, log);

	FILE* f = fopen(file_path, "a");
	if(f!=NULL)
	{
		fprintf(f, errorLog);
	}
	fclose(f);
}


void ErrorLog_initFolder(){
	ErrorLog_createFolder();
}

static void ErrorLog_createFolder(){
	struct stat st = {0};
	char path[512];
	getcwd(path, 512);
	strcat(path, "\\ErrorLog");

	if (stat(path, &st) == -1) {
	    mkdir("ErrorLog");
	}
}


static void GetCurrentDateTime(char* dest)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(dest, "%02d/%02d/%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
