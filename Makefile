
SRC=argparse.c  main.c  play.c  raw_mode.c  record.c  testcase.c


all:
	gcc  -g -Wall -Wextra $(SRC) -I . -o totty
