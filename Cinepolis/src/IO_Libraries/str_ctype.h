
#ifndef VIEW_IO_MY_CTYPE_H_
#define VIEW_IO_MY_CTYPE_H_



#endif /* VIEW_IO_MY_CTYPE_H_ */


int str_tolower(char *str);
int str_totitle(char *str);
int str_nochange(char *str);
int str_shorten(char* shorted, int size, const char* string, int max);

char* maskify(char* masked, const char* string, char mask);
