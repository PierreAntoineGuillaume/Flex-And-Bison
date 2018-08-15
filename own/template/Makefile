target: flex.l bison.y
	bison -d bison.y
	flex flex.l
	cc -o $@ bison.tab.c flex.yy.c -lfl
