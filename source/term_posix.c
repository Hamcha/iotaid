/*
	POSIX implementation for term_* functions
	Uses ANSI escape codes and TIOCGWINSZ.

	Note: TIOCGWINSZ is not POSIX compliant, but
	      appears to work everywhere.
*/
#include <sys/ioctl.h>
#include <stdio.h>
#include "term.h"

void term_blink(int enable) {
	if (enable == 0) {
		printf("\033[5m");
	} else {
		printf("\033[0m");
	}
}

void term_clear() {
	printf("\033[2J");
}

void term_goto(int x, int y) {
	printf("\033[%d;%df", y, x);
}

TermSize term_size() {
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
	TermSize t;
	t.rows = w.ws_row;
	t.cols = w.ws_col;
	return t;
}