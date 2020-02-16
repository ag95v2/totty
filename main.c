#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"
#include "play.h"
#include "raw_mode.h"
#include "record.h"
#include "testcase.h"
#include <sys/time.h>

int main(int argc, char **argv, char **env)
{
	union params options;
	mode         m;

	m = get_mode(argc, argv, &options);
	if (m == invalid)
	{
		printf("%s", BAD_ARG_MSG);
		return (1);
	}
	else if (m == record)
	{
		record_dump(&options);
		return (0);
	}
	else if (m == play)
	{
		read_play(&options, env);
		return (0);
	}
	return (0);
}
