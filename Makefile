clean:
	find . -not \( -wholename "./.git*" -o -name Makefile -o -name readme.md -o -name fbmake -o -name "*.l" -o -name "*.y" \) -type f -exec rm {} \+;
