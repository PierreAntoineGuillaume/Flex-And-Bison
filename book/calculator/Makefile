
dir=(make-build)

fb1-5: lex.yy.c fb1-5.tab.c fb1-5.tab.h
	 g++ -o $@ fb1-5.tab.c lex.yy.c -lfl -lm

fb1-5.tab.c: fb1-5.y
	bison -d fb1-5.y

fb1-5.tab.h: fb1-5.y
	bison -d fb1-5.y

lex.yy.c: fb1-5.l
	flex fb1-5.l
