#Flags
CFLAGS  = -stdlib=libstdc++

#Directories
INC_DIR = '/usr/bin/clang'

QMAKE_CC=gcc

all: lex.yy.c y.tab.c y.tab.h
		gcc lex.yy.c y.tab.c -o shellProject.exe

y.tab.h: y.tab.c

y.tab.c: shellProject.y
		yacc -dv shellProject.y

lex.yy.c: shellProject.l
		lex shellProject.l

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h main
