CC = cc

SRC = util.c main.c toc.c
DIST = ./build/wbg

all: compile

compile: 
	${CC} ${SRC} -o ${DIST}

.PHONY: all clean copmile
