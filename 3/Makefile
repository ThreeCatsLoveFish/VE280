.PHONY: clean debug test release format

CC=clang++
CFLAGS=-Wall -Werror -Iinclude/ -g -DLOCAL

p3: build/p3.o build/simulation.o
	$(CC) $(CFLAGS) -o $@ $^
	@echo "p3 release!"

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

test: p3
	@./p3 test/species test/world-tests/outside-world 5 > ./tmp/outside-world.out
	@diff ./tmp/outside-world.out test/world-tests/outside-world.answer
	@echo "Outside-world Pass!"
	@./p3 test/species test/world-tests/overlap-world 5 > ./tmp/overlap-world.out
	@diff ./tmp/overlap-world.out test/world-tests/overlap-world.answer
	@echo "Overlap-world Pass!"
	@./p3 test/species test/world-tests/world1 5 > ./tmp/world1-concise.out
	@diff ./tmp/world1-concise.out test/world-tests/world1-concise.answer
	@echo "World1-concise Pass!"
	@./p3 test/species test/world-tests/world2 20 > ./tmp/world2-concise.out
	@diff ./tmp/world2-concise.out test/world-tests/world2-concise.answer
	@echo "World2-concise Pass!"
	@./p3 test/species test/world-tests/world3 40 > ./tmp/world3-concise.out
	@diff ./tmp/world3-concise.out test/world-tests/world3-concise.answer
	@echo "World3-concise Pass!"
	@./p3 test/species test/world-tests/world1 5 v > ./tmp/world1-verbose.out
	@diff ./tmp/world1-verbose.out test/world-tests/world1-verbose.answer
	@echo "World1-verbose Pass!"
	@./p3 test/species test/world-tests/world2 20 verbose > ./tmp/world2-verbose.out
	@diff ./tmp/world2-verbose.out test/world-tests/world2-verbose.answer
	@echo "World2-verbose Pass!"
	@./p3 test/species test/world-tests/world3 40 verbose > ./tmp/world3-verbose.out
	@diff ./tmp/world3-verbose.out test/world-tests/world3-verbose.answer
	@echo "World3-verbose Pass!"
	@rm -rf ./tmp/*
	@echo "Test PASSED!"

release: format
	tar -cf release.tar -C ./src/ simulation.cpp p3.cpp -C ../include/ simulation.h 

format:
	clang-format -i include/*.h src/*.cpp

clean:
	rm -f ./tmp/*
	rm -f ./build/*
	rm ./p3
	rm ./release.tar
