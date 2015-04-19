all: clean y.tab.h y.tab.c lex.yy.c shellProject run

shellProject: lex.yy.c y.tab.c y.tab.h
		gcc -o shellProject *.c

y.tab.h y.tab.c: shellProject.y
		yacc -dy shellProject.y

lex.yy.c: shellProject.l
		flex shellProject.l

run:
	./shellProject

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h shellProject