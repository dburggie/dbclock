#include <dbclock.h>
#include <ncurses.h>
#include <time.h>

int main(void) {
	
	int y, x;
	if (dbc_init(&y, &x))
		return 0;
	
	int ch;
	time_t timestamp = time(NULL);
	while ( (ch = getch()) != KEY_F(2) ) {
		if (timestamp != time(NULL)) {
			dbc_update(y,x);
		}
	}

	dbc_cleanup();

	return 0;
}


