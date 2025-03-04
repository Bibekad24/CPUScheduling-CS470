# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Build both executables
all: sjf rr

# Compile Shortest Job First (SJF) Preemptive
sjf: SJF_final.c
	$(CC) $(CFLAGS) -o sjf SJF_final.c

# Compile Round Robin (RR)
rr: RR_final.c
	$(CC) $(CFLAGS) -o rr RR_final.c

# Clean up executables
clean:
	rm -f sjf rr
