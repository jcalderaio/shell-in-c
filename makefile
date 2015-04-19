all: clean y.tab.h y.tab.c lex.yy.c shellProject build

shellProject: lex.yy.c y.tab.c y.tab.h
		gcc -Wall -c lex.yy.c y.tab.c shellProject.c

y.tab.h y.tab.c: shellProject.y
		bison -dy shellProject.y

lex.yy.c: shellProject.l
		flex shellProject.l

build:
	gcc -o shellProject lex.yy.o y.tab.o shellProject.o

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h shellProject