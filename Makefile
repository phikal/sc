CC=gcc
OUT=sc
FILES=	sc.c\
	rpn.c\
	stack.c\
	calc.c\
	num.c
COPTS=-std=c99 -lm -Wall -Wextra -O2

include config.mk

all:
	${CC} ${FILES} ${COPTS} -o ${OUT}

install:
	@mv sc ${INSTALL}
	@echo Installed

uninstall:
	@rm ${INSTALL}/sc
	@echo Uninstalled

TEST=test

clean:
	@[ -f sc ] && rm sc
	@[ -f ${TEST} ] && rm ${TEST}
	@echo Cleaned up

stack_test:
	@echo Test results should equal test numbers
	@${CC} stack.c calc.c num.c tests/stack_test.c ${COPTS} -O0 -o ${TEST}
	@./${TEST}
	@rm ${TEST}

calc_test:
	@echo Test results should equal test numbers
	@${CC} calc.c num.c tests/calc_test.c ${COPTS} -O0 -o ${TEST}
	@./${TEST}
	@rm ${TEST}

help:
	@echo "Type 'make; make install' to install sc"
