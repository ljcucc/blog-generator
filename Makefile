CC = cc

SRC = util.c main.c toc.c libs/cJSON.c
DIST = ./build/
OUT = wbg

include config.mk

all: compile

compile:
	${CC} ${SRC} -o ${DIST}/${OUT}

debug:
	${CC} ${SRC} -o ${DIST}/${OUT} -v

run: compile
	${DIST}${OUT} ${TEST_INPUT_PATH} ${TEST_OUTPUT_PATH} ${TEST_TEMPLATE_PATH}

.PHONY: all clean copmile debug run
