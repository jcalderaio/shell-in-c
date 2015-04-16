all: clean y.tab.h y.tab.c lex.yy.c shellProject run

shellProject: lex.yy.c y.tab.c y.tab.h
		cc lex.yy.c y.tab.c shellProject.c -o shellProject

y.tab.h y.tab.c: shellProject.y
		yacc -dv shellProject.y

lex.yy.c: shellProject.l
		lex shellProject.l

run:
	./shellProject

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h shellProject