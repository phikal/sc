CC=gcc
OUT=scl
FILES=	scl.c\
	cfunc.c\
	snode.c\
	vtree.c
#COPTS=-std=c99 -lm -Wall -Wextra -O2
COPTS=-std=c99 -lm -O0 -ggdb

# include ../config.mk

all:
	${CC} ${FILES} ${COPTS} -o ${OUT}
