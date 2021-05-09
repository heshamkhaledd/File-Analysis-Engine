# Make Variables
CC = g++
SRCS = src/*.cpp
INC = inc/
CPPFLAGS = -I${INC} -Wall
EXEC = File_Engine
OUT_DIR = build
RM_CMD = cd ${OUT_DIR} && rm _time_.txt

#  GNU MAKE Macros
START_TIME=date +%s > ${OUT_DIR}/_time_.txt
TIME_MACRO=$$(($$(date +%s)-$$(cat ${OUT_DIR}/_time_.txt))) sec

all:
	@echo 'Building Target: $@'
	@echo 'Invoking: g++ Compiler/Linker'
	mkdir -p ${OUT_DIR}
	@${START_TIME}
	${CC} ${SRCS} ${CPPFLAGS} -o ${OUT_DIR}/${EXEC}.exe
	@echo Compilation Time: ${TIME_MACRO}
	@echo 'Finished building target: $@'
	@${RM_CMD}