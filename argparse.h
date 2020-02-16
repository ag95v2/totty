#ifndef ARGPARSE_H
#define	ARGPARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HELP_MSG "Usage:\n"\
	"totty has 2 operating modes: record mode and play mode\n"\
	"\nRecord mode command format:\n"\
	"./totty --record -o FNAME - record interactive session to file FNAME\n"\
	"\nPlay mode command format:\n"\
"./totty [--file FILE | --interactive] (--speedup N) [--attach PID | --cmd args]\n"\
	"--file FILE - take input from file\n"\
	"--interactive - start interactive session\n"\
	"--speedup or -s - increase speed N times\n"\
	"--attach PID - redirect user activity to stdin of PID (should be root)\n"\
	"--cmd args - Pass path to binary that should be executed\n"

#define BAD_ARG_MSG "Bad argument format. \n"\
					"Run ./totty --help for clarifications\n"

typedef enum	
{
	record, 
	play,
	invalid
} mode;

typedef	struct	params_rec
{
	char		*fname;
}				t_params_rec;

typedef	struct	params_play
{
	char		*fname;
	int			interactive;
	int			speedup;
	pid_t		pid;
	char		**cmd_argv;
	int			cmd_argc;
}				t_params_play;

union	params
{
	t_params_rec	record;
	t_params_play	play;
};

void	verbose_play_options(union params options);
void	verbose_record_options(union params options);

mode	get_mode(int argc, char **argv, union params *options);

#endif
