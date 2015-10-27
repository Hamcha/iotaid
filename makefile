ifndef CC
	CC = gcc
endif

ifdef DJGPP
	PLATFORM = term_dos.o
else
	# Assume POSIX for now, add support for more systems later (if we care)
	PLATFORM = term_posix.o
endif

CFLAGS=-Wall -g -O2 -Wstrict-aliasing=2
LFLAGS=-llua

OBJ = config.o game.o main.o

iotaid.exe: $(PLATFORM) $(OBJ)
	$(CC) $(LFLAGS) -o iotaid.exe $(PLATFORM) $(OBJ)

%.o: ./source/%.c
	$(CC) $(CFLAGS) -c $<