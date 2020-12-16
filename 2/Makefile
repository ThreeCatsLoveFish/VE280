.PHONY: all test clean

all: list tree

test: all
	@./build/p2_test_list
	@./build/p2_test_tree

list: src/p2.cpp src/recursive.cpp test/test_list.cpp
	@g++ -Wall $^ -o build/p2_test_list

tree: src/p2.cpp src/recursive.cpp test/test_tree.cpp
	@g++ -Wall $^ -o build/p2_test_tree

clean:
	@rm ./build/*
