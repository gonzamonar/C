
#include "../IO_Libraries/str_ctype.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int str_totitle(char *str){
	int outcome = 0;
	if(str != NULL){
		outcome = 1;
		str[0] = toupper(str[0]);
		while(*str != '\0'){
			if(*str == ' '){
				*(str+1) = toupper(*(str+1));
			}else{
				*(str+1) = tolower(*(str+1));
			}
			str++;
		}
	}
	return outcome;
}

int str_tolower(char *str){
	int outcome = 0;
	if(str != NULL)
	{
		outcome = 1;
		while(*str != '\0')
		{
			*str = tolower(*str);
			str++;
		}
	}
	return outcome;
}


int str_nochange(char *str){
	return 1;
}


int str_shorten(char* shorted, int size, const char* src, int max){
  int outcome = 0;
  int len = strlen(src);
  if(shorted != NULL && src != NULL && size < len && len > max && size > max){
	  outcome = 1;
	  for(int i=0; i<max; i++){
		  if(i<max-3){
			  shorted[i] = src[i];
		  }else if(i>=max-3){
			  shorted[i] = '.';
		  }
	  }
	  shorted[max] = '\0';
  }
  return outcome;
}

char* maskify(char* masked, const char* string, char mask){
  int len = strlen(string);
  strcpy(masked, string);

  if(len>4){
    for(int i=0; i<len-4; i++){
      masked[i] = mask;
    }
  }
  return masked;
}
