
match_url: lex.yy.cc
	g++ $< -lfl -o $@

lex.yy.cc: match_url.l
	flex $<

.PHONY: clean
clean:
	rm -rf lex.yy.cc match_url
