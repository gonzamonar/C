

#include "randomizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randomize_Integer(int seed, int min, int max){
	int randNum;
	time_t t;

	srand(seed*time(&t));
	randNum = (rand() % (max - min + 1) + min);
	return randNum;
}


short randomize_Boolean(int seed){
	short randNum;
	time_t t;

	srand(seed*time(&t));
	randNum = (rand() % 2);
	return randNum;
}


void randomize_Date(int seed, char* dest){
	int year = 2023;
	int month = randomize_Integer(seed, 1, 12);
	int maxday = 31;

	if(month==2){
		maxday = 28;
	}else if(month == 4 || month == 6 || month == 9 || month == 11){
		maxday -= 1;
	}

	int day = randomize_Integer(seed*month*maxday, 1, maxday);

	sprintf(dest, "%02d/%02d/%d", day, month, year);
}
