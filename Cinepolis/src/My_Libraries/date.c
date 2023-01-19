
#include "date.h"

#include <stdio.h>
#include <string.h>


//Método de Sakamoto
int dayofweek(int d, int m, int y){
    const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if(m<3)    {
        y -= 1;
    }
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


int dayofweek_str(char* strDate){
	Date date;
	sscanf(strDate, "%d/%d/%d", &date.day, &date.month, &date.year);
    return dayofweek_date(date);
}


int dayofweek_date(Date date){
    return dayofweek(date.day, date.month, date.year);
}


void nameoftheday(char* dest, int weekDay, char* lang){
	int language = (strcmp(lang, "EN")==0) ? 2 : 1 ;

	switch(weekDay){
	case 0:
		(language==1) ? strcpy(dest, "Domingo") : strcpy(dest, "Sunday") ;
		break;
	case 1:
		(language==1) ? strcpy(dest, "Lunes") : strcpy(dest, "Monday") ;
		break;
	case 2:
		(language==1) ? strcpy(dest, "Martes") : strcpy(dest, "Tuesday") ;
		break;
	case 3:
		(language==1) ? strcpy(dest, "Miércoles") : strcpy(dest, "Wednesday") ;
		break;
	case 4:
		(language==1) ? strcpy(dest, "Jueves") : strcpy(dest, "Thursday") ;
		break;
	case 5:
		(language==1) ? strcpy(dest, "Viernes") : strcpy(dest, "Friday") ;
		break;
	case 6:
		(language==1) ? strcpy(dest, "Sábado") : strcpy(dest, "Saturday") ;
		break;
	}
}
