#include "play.h"

void char_to_tty(int fd, char c)
{
	if (ioctl(fd, TIOCSTI, &c) < 0)
	{
		perror("ioctl");
		exit(1);
	}
}

pid_t new_process(union params *options, char **env)
{
	pid_t child;

	child = fork();
	if (child == 0)
	{
		execve(options->play.cmd_argv[0], options->play.cmd_argv, env);
		perror("execve");
		exit(1);
	}
	return (child);
}

void input_from_file(union params *options, int process_fd)
{
	t_testcase *l;
	char        c;
	long long   delay;

	l = read_testcase(options);
	if (!l)
		exit(0);
	while (extract_single_action(&l, &c, &delay))
	{
		if (options->play.speedup)
			delay = delay / options->play.speedup;
		if (usleep(delay * 1000) == -1)
		{
			perror("usleep");
			exit(1);
		}
		char_to_tty(process_fd, c);
	}
}

void input_interactive(int process_fd)
{
	char c;

	enableRawMode();
	while ((c = getc(stdin)) != EXIT_CHAR)
		char_to_tty(process_fd, c);
}

int read_play(union params *options, char **env)
{
	pid_t pid;
	char  terminal_stdin[FNAME_LEN];
	int   fd;

	if (getuid() != 0)
		printf("%s\n", "WARNING: This program should be run under root!");
	if (options->play.pid)
		pid = options->play.pid;
	else
		pid = new_process(options, env);
	sprintf(terminal_stdin, "/proc/%d/fd/0", pid);
	fd = open(terminal_stdin, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (options->play.interactive)
		input_interactive(fd);
	else
		input_from_file(options, fd);
	if (options->play.interactive)
		kill(pid, SIGKILL);
	close(fd);
	return (1);
}
