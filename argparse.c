#include "argparse.h"

static void init_params_union(union params *options)
{
	options->play.fname = NULL;
	options->play.interactive = 0;
	options->play.speedup = 0;
	options->play.pid = 0;
	options->play.cmd_argv = NULL;
	options->play.cmd_argc = 0;
}

static void print_usage(void)
{
	printf("%s", HELP_MSG);
}

/* --word || -w */

static int looks_like_word(char *s, char *word)
{
	if (!strncmp(s, "--", 2) && !strcmp(s + 2, word))
		return (1);
	if (*s == '-' && *(s + 1) == *word)
		return (1);
	return (0);
}

static mode fill_play_params(int argc, char **argv, union params *options)
{
	int  i;
	mode hypotesis;

	hypotesis = play;
	init_params_union(options);
	i = 0;
	while (++i < argc) /* Setup flags */
	{
		if (looks_like_word(argv[i], "file") && argc > i + 1)
			options->play.fname = argv[i + 1];
		if (looks_like_word(argv[i], "interactive"))
			options->play.interactive = 1;
		if (looks_like_word(argv[i], "speedup") && argc > i + 1)
			options->play.speedup = atoi(argv[i + 1]);
		if (looks_like_word(argv[i], "attach") && argc > i + 1)
			options->play.pid = atoi(argv[i + 1]);
		if (looks_like_word(argv[i], "cmd") && argc > i + 1)
		{
			options->play.cmd_argv = argv + i + 1;
			options->play.cmd_argc = argc - i - 1;
		}
	}

	/* Detect mutually exclusive flags */
	if (options->play.pid && options->play.cmd_argc)
		hypotesis = invalid;
	if (options->play.fname && options->play.interactive)
		hypotesis = invalid;
	/* Dectect abscence of nessessary flag */
	if (!options->play.pid && !options->play.cmd_argc)
		hypotesis = invalid;
	if (!options->play.fname && !options->play.interactive)
		hypotesis = invalid;
	return (hypotesis);
}

static mode fill_record_params(int argc, char **argv, union params *options)
{
	if (argc == 4 && looks_like_word(argv[2], "output"))
	{
		options->record.fname = argv[3];
		return (record);
	}
	return (invalid);
}

mode get_mode(int argc, char **argv, union params *options)
{
	mode hypotesis;

	if (argc < 2)
	{
		return (invalid);
	}
	if (looks_like_word(argv[1], "help"))
	{
		print_usage();
		exit(0);
	}
	hypotesis = looks_like_word(argv[1], "record") ? record : play;
	if (hypotesis == record) /* RECORD mode or invalid */
		return (fill_record_params(argc, argv, options));
	else /* PLAY mode or invalid*/
		return (fill_play_params(argc, argv, options));
}

void verbose_play_options(union params options)
{
	printf("Filename: %s\n", options.play.fname);
	printf("Interactive: %d\n", options.play.interactive);
	printf("Speedup: %d\n", options.play.speedup);
	printf("PID: %d\n", options.play.pid);
	printf("First arg (if exists):%p\n", options.play.cmd_argv);
	printf("N args: %d\n", options.play.cmd_argc);
}

void verbose_record_options(union params options)
{
	printf("%s\n", options.record.fname);
}
