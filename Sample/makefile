CC=gcc
DEBUG=-g -O0
CFLAGS=$(DEBUG)

all: execvp-ex1.exe mtu-shell.exe

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

execvp-ex1.exe: execvp-ex1.o
	$(CC) -o $@ $<

mtu-shell.exe: mtu-shell.o
	$(CC) -o $@ $<

clean:
	rm -f *.o  execvp-ex1.exe mtu-shell.exe \#*\# *~
