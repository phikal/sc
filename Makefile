include config.mk

CC=gcc
OUT=sc
FILES=	sc.c\
	rpn.c\
	stack.c\
	calc.c
COPTS=-std=c99 -lm -Wall -Wextra

all:
	${CC} ${FILES} ${CFLAGS} ${COPTS} -o ${OUT}

install:
	mv sc ${INSTALL}

uninstall:
	rm ${INSTALL}/sc

TEST=tst

clean:
	[ -f sc ] && rm sc
	[ -f ${TEST} ] && rm ${TEST}

stack_test:
	${CC} stack.c calc.c test/stack_test.c ${CFLAGS} ${COPTS} -o ${TEST}
	./${TEST}
	rm ${TEST}

calc_test:
	${CC} calc.c test/calc_test.c ${CFLAGS} ${COPTS} -o ${TEST}
	./${TEST}
	rm ${TEST}

help:
	@echo "Type 'make; make install' to install sc"
