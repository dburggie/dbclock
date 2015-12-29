#ifndef __DBCLOCK_H
#define __DBCLOCK_H

#include <ncurses.h>

typedef struct Time_t Time_t;

struct Time_t {
	//time of day
	int sec; //0-60
	int min; //0-59
	int hr ; //0-23

	//date
	int mon; //1-12
	int day; //1-31
	int yr ; //0-99 (actual year mod 100)
};

//util.c
int dbc_init(int * y0, int * x0);
void dbc_cleanup();
Time_t dbc_get_time();
void dbc_update(int y0, int x0);

//data.c
extern const char dbc_chars[12][5][4];

#endif
