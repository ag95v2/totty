#ifndef RAW_MODE_H
#define RAW_MODE_H

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode();
void enableRawMode();

#endif
