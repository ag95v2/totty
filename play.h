#ifndef PLAY_H
#define PLAY_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include "record.h"
#include "raw_mode.h"
#include "testcase.h"
#include "stdio.h"

#include <signal.h>

#define FNAME_LEN (15 + sizeof("/proc//fd/0"))

int	 read_play(union params *options, char **env);
#endif
