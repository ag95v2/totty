#ifndef TESTCASE_H
#define TESTCASE_H

#include <unistd.h>
#include <fcntl.h>

#include "argparse.h"

#define EOF_REACHED 0
#define NO_EOF 1

/*
** Interface of testcase type (linked list actually)
*/

typedef struct	s_testcase
{
	struct s_testcase	*next;
	char		c;
	long long	delay_ms;
}				t_testcase;

int		extract_single_action(t_testcase **l, char *c, long long *delay);
t_testcase	*read_testcase(union params *options);
void	dump_testcase(t_testcase *l, union params *options);
t_testcase			*append_testcase(char c, long long delay_ms);
t_testcase	*new_testcase(char c, long long delay_ms);

#endif
