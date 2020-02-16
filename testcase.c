#include "testcase.h"

t_testcase *new_testcase(char c, long long delay_ms)
{
	t_testcase *res;

	res = malloc(sizeof(t_testcase));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->c = c;
	res->delay_ms = delay_ms;
	return (res);
}

/*
** Add new element to the end of linked list
** Return NULL case of errors
** Otherwise return pointer to start
*/

t_testcase *append_testcase(char c, long long delay_ms)
{
	static t_testcase *start;
	static t_testcase *end;
	t_testcase *new;

	if (!(new = new_testcase(c, delay_ms)))
		return (NULL);
	if (!start)
	{
		start = new;
		end = start;
		return (start);
	}
	end->next = new;
	end = new;
	return (start);
}

void dump_testcase(t_testcase *l, union params *options)
{
	int fd;

	fd = open(options->record.fname, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror(options->record.fname);
		exit(1);
	}

	while (l)
	{
		write(fd, &(l->c), sizeof(l->c));
		write(fd, &(l->delay_ms), sizeof(l->delay_ms));
		l = l->next;
	}
	close(fd);
}

/*
** Read next entry from file
** Exit in case of any errors
** Return 0 if EOF reached
*/

static int xread(int fd, char *c, long long *delay)
{
	int nchar;

	nchar = read(fd, c, sizeof(*c));
	if (nchar == 0)
		return (EOF_REACHED);
	if (nchar == -1)
	{
		perror("read");
		exit(1);
	}
	nchar = read(fd, delay, sizeof(*delay));
	if (nchar < (int)sizeof(*delay))
	{
		printf("%s\n", "Bad file format");
		exit(1);
	}
	return (NO_EOF);
}

t_testcase *read_testcase(union params *options)
{
	int         fd;
	char        c;
	long long   delay_ms;
	t_testcase *res;

	fd = open(options->play.fname, O_RDONLY);
	if (fd == -1)
	{
		perror(options->play.fname);
		exit(1);
	}

	res = 0;
	while (xread(fd, &c, &delay_ms) != EOF_REACHED)
	{
		res = append_testcase(c, delay_ms);
		if (!res)
		{
			printf("%s\n", "No memory!");
			exit(1);
		}
	}
	close(fd);
	return (res);
}

int extract_single_action(t_testcase **l, char *c, long long *delay)
{
	t_testcase *tmp;

	tmp = *l;
	if (!tmp)
		return (0);
	*l = (*l)->next;
	*c = tmp->c;
	*delay = tmp->delay_ms;
	free(tmp);
	return (1);
}
