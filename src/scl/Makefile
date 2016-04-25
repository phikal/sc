CC=gcc
OUT=scl
FILES=  scl.c\
	vtree.c\
	snode.c\
CFUNC= $(shell find cfunc -type f)

#COPTS=-std=c99 -lm -Wall -Wextra -O2
COPTS=-std=c99 -lm -O0 -ggdb

# include ../config.mk

all:
	${CC} ${FILES} ${CFUNC} ${COPTS} -o ${OUT}
