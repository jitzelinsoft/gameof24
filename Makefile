clean:
	rm -rf ./bin

build:
	mkdir -p ./bin
	gcc -O2 -std=c99 -pedantic -Wall -o ./bin/gameof24 src/main.c -lm

run: clean build
	./bin/gameof24
