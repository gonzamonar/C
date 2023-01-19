
#ifndef VIEW_GENERALIO_H_
#define VIEW_GENERALIO_H_

typedef struct{
	int day;
	int month;
	int year;
}Date;

#endif /* VIEW_GENERALIO_H_ */

int dayofweek(int d, int m, int y);
int dayofweek_str(char* strDate);
int dayofweek_date(Date date);
void nameoftheday(char* dest, int weekDay, char* lang);
