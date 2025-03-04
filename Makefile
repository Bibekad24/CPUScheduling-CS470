CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: sjf rr

sjf: SJF_final.c
	$(CC) $(CFLAGS) -o sjf SJF_final.c

rr: RR_final.c
	$(CC) $(CFLAGS) -o rr RR_final.c

clean:
	rm -f sjf rr
