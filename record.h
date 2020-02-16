#ifndef RECORD_H
#define RECORD_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/time.h>
#include "argparse.h"
#include "raw_mode.h"
#include "testcase.h"

#ifndef EXIT_CHAR
#define EXIT_CHAR 'q'
#endif

void	record_dump(union params *options);

#endif
