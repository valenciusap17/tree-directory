.PHONY: compile test

compile:
	gcc main.c indent.c -o bin/tree

test:
	./bin/tree ./..

run:
	compile
	test