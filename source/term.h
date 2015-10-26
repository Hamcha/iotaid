#ifndef _TERM_H
#define _TERM_H

//! Terminal size in rows/columns
typedef struct termsize_t {
	int rows; //!< Row count
	int cols; //!< Column count
} TermSize;

/*! \brief Set cursor blinking
 *
 *  Used to disable the cursor when writing text and setting it back on
 *  when as soon as there needs to be user interaction
 *
 *  \param enable Enable/Disable blinking: 1: Enable 0: Disable
 */
void term_blink(int enable);

/*! \brief Clears the screen
 */
void term_clear();

/*! \brief Move cursor to specified row/column
 *
 *  \param x Column to move to
 *  \param y Row to move to
 */
void term_goto(int x, int y);

/*! \brief Retrieve current terminal window size in row/column counts
 *
 *  \return TermSize struct with row/column counts
 */
TermSize term_size();

#endif