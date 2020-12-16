.PHONY: all release clean test

CC=clang++
FLAGS=-std=c++11 -Wall -Werror -Werror=sign-compare -Werror=uninitialized -Iinclude
SRC=$(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

all: p4

p4: $(SRC)
	$(CC) -o $@ $^ $(FLAGS)

build/%.o: src/%.cpp
	$(CC) -o $@ -c $^ $(FLAGS)

test: p4
	./p4 ENUM < test/sat.in > test/test_enum.out
	diff test/test_enum.out test/sat_enum.out
	./p4 DEDUCT < test/sat.in > test/test_deduct.out
	diff test/test_deduct.out test/sat_deduct.out
	./p4 ENUM < test/unsat.in > test/test_enum.out
	diff test/test_enum.out test/unsat_enum.out
	./p4 DEDUCT < test/unsat.in > test/test_deduct.out
	diff test/test_deduct.out test/unsat_deduct.out
	rm test/test*

format:
	clang-format -i $(wildcard src/*.cpp)

release: format
	tar -cvf 4.tar -C src/ $(patsubst src/%, %, $(wildcard src/*.cpp))

clean:
	rm -f build/*
	rm 4.tar
	rm p4
