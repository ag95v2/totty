#include "record.h"

long long current_timestamp()
{
	struct timeval te;

	gettimeofday(&te, NULL);
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

/*
** Create a linked list and dump it into the file
*/

void record_dump(union params *options)
{
	int         c;
	long long   time, prev;
	t_testcase *start;

	printf("Press '%c' to exit\n", EXIT_CHAR); /* TODO: customize exit char */
	enableRawMode();
	start = NULL;
	time = prev = current_timestamp();
	while ((c = getc(stdin)) != EXIT_CHAR)
	{
		time = current_timestamp();
		if (!(start = append_testcase(c, time - prev)))
		{
			printf("%s\n", "Could not allocate memory!");
			exit(1);
		}
		prev = time;
	}
	dump_testcase(start, options);
}
