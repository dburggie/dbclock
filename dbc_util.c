#include <ncurses.h>
#include <dbclock.h>
#include <time.h>

static void dbc_printc(int y, int x, int c_index);
static void dbc_printn(int y, int x, int n);

//to implement here:
//  int dbc_init(int *y0, int *x0)
//  void dbc_cleanup()
//	Time_t dbc_get_time()
//	void dbc_update(int y0, int x0)





int dbc_init(int * y0, int * x0) {

	initscr();
	halfdelay(1);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		attrset(COLOR_PAIR(1));
	}

	int rowc, colc;
	getmaxyx(stdscr,rowc,colc);

	if (rowc < 11 || colc < 31) {
		printw("screen too small (min 31x11)");
		dbc_cleanup();
		return 1;
	}

	if (rowc % 2) *y0 = rowc / 2 - 5;
	else *y0 = rowc / 2 - 6;

	if (colc % 2) *x0 = colc / 2 - 15;
	else *x0 = colc / 2 - 16;

	return 0;
}





void dbc_cleanup() {
	
	if (has_colors()) {
		attroff(COLOR_PAIR(1));
	}

	endwin();
}





Time_t dbc_get_time() {
	Time_t t;

	//get time from time.h
	time_t et = time(NULL);

	//convert time object to local time
	struct tm *tmp = localtime(&et);

	//fill our struct
	t.sec = tmp->tm_sec;
	t.min = tmp->tm_min;
	t.hr  = tmp->tm_hour;
	t.day = tmp->tm_mday;
	t.mon = tmp->tm_mon + 1;
	t.yr  = tmp->tm_year % 100;

	return t;
}





void dbc_update(int y0, int x0) {

	Time_t t = dbc_get_time();
	
	//handle date
	dbc_printn(y0,x0,t.mon);
	dbc_printc(y0,x0 + 8, 11);
	dbc_printn(y0,x0 + 12, t.day);
	dbc_printc(y0,x0 + 20, 11);
	dbc_printn(y0,x0 + 24, t.yr);

	//handle time
	y0 += 6;
	dbc_printn(y0,x0, t.hr);
	dbc_printc(y0,x0 + 8, 10);
	dbc_printn(y0,x0 + 12, t.min);
	dbc_printc(y0,x0 + 20, 10);
	dbc_printn(y0,x0 + 24, t.sec);

	refresh();
}


static void dbc_printc(int y, int x, int c_index) {
	int i;
	for (i = 0; i < 5; i++)
		mvwprintw(stdscr,y + i, x, dbc_chars[c_index][i]);
}

static void dbc_printn(int y, int x, int n) {
	dbc_printc(y,x,     n / 10);
	dbc_printc(y,x + 4, n % 10);
}
