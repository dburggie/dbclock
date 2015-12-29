
INSTALLDIR = ~/bin

CFLAGS = -I. -Wall -D_DEBUG
CC = gcc ${CFLAGS}

LIB = -lncurses

EXE = dbclock

all: ${EXE}

install: all
	cp ${EXE} ${INSTALLDIR}/${EXE}

clean:
	rm -f *.o
	rm -f ${EXE}

dbclock: dbc_main.o dbc_data.o dbc_util.o
	${CC} -o $@ $^ ${LIB}

dbc_main.o: dbc_main.c dbclock.h
	${CC} -o $@ -c $< ${LIB}

dbc_data.o: dbc_data.c dbclock.h
	${CC} -o $@ -c $<

dbc_util.o: dbc_util.c dbclock.h
	${CC} -o $@ -c $< ${LIB}


