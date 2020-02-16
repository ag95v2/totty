#include "raw_mode.h"

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode); /* Stdlib useful function*/

	struct termios raw = orig_termios;
	raw.c_iflag &= ~(IXON);                 /* Disable Ctrl+s (suspend input)*/
	raw.c_lflag &= ~(ECHO | ICANON | ISIG); /* Disable the signals */
	raw.c_iflag &= ~(IEXTEN);               /* Disable Ctrl+v (escape char) */
	raw.c_iflag &= ~(ICRNL | IXON); /* Disable Ctrl+m and Ctrl+g (newline)*/
	raw.c_oflag &= ~(OPOST);        /* Disable \n to \r\n conversion*/
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
