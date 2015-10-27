/*
	DOS implementation for term_* functions
	Uses DJGPP exclusive functions.
*/
#include <pc.h>
#include "term.h"

void term_blink(int enable) {
	if (enable == 0) {
		ScreenAttrib &= 0x7F;
	} else {
		ScreenAttrib |= 0x80;
	}
}

void term_clear() {
	ScreenClear();
}

void term_goto(int x, int y) {
	ScreenSetCursor(x, y);
}

TermSize term_size() {
	TermSize t;
	t.rows = ScreenRows();
	t.cols = ScreenCols();
	return t;
}