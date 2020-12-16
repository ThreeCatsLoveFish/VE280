.PHONY: test format release clean

ERROR=/dev/null
ECHO=echo "==VE280=="
CC=clang++
FLAGS=-Wall -Werror -Iinclude/ -g

test: test_dList test_cleaner test_call
	@$(ECHO)
	@$(ECHO) "VE280 Project 5 Tester"
	@$(ECHO) "Copyright @Threecats"
	@$(ECHO)

%: src/%.cpp
	$(CC) -o $@ $(FLAGS) $^

test_dList: testDList
	@$(ECHO)
	@$(ECHO) "DList TEST"
	@valgrind --leak-check=full ./testDList 2>$(ERROR)
	@$(ECHO) "DList PASS"
	@$(ECHO)

test_cleaner: cleaner
	@$(ECHO)
	@$(ECHO) "Cleaner TEST"
	@valgrind --leak-check=full ./cleaner < test/cleaner/in/1 1> tmp/tex.test1 2>$(ERROR)
	@diff tmp/tex.test1 test/cleaner/out/1
	@$(ECHO) "Case 1 PASS!"
	@valgrind --leak-check=full ./cleaner < test/cleaner/in/2 1> tmp/tex.test2 2>$(ERROR)
	@diff tmp/tex.test2 test/cleaner/out/2
	@$(ECHO) "Case 2 PASS!"
	@valgrind --leak-check=full ./cleaner < test/cleaner/in/3 1> tmp/tex.test3 2>$(ERROR)
	@diff tmp/tex.test3 test/cleaner/out/3
	@$(ECHO) "Case 3 PASS!"
	@valgrind --leak-check=full ./cleaner < test/cleaner/in/4 1> tmp/tex.test4 2>$(ERROR)
	@diff tmp/tex.test4 test/cleaner/out/4
	@$(ECHO) "Case 4 PASS!"
	@$(ECHO) "Cleaner PASS"
	@$(ECHO)

test_call: call
	@$(ECHO)
	@$(ECHO) "Call TEST"
	@valgrind --leak-check=full ./call < test/call/in/1 1> tmp/call.test1 2>$(ERROR)
	@diff tmp/call.test1 test/call/out/1
	@$(ECHO) "Case 1 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/2 1> tmp/call.test2 2>$(ERROR)
	@diff tmp/call.test2 test/call/out/2
	@$(ECHO) "Case 2 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/3 1> tmp/call.test3 2>$(ERROR)
	@diff tmp/call.test3 test/call/out/3
	@$(ECHO) "Case 3 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/4 1> tmp/call.test4 2>$(ERROR)
	@diff tmp/call.test4 test/call/out/4
	@$(ECHO) "Case 4 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/5 1> tmp/call.test5 2>$(ERROR)
	@diff tmp/call.test5 test/call/out/5
	@$(ECHO) "Case 5 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/6 1> tmp/call.test6 2>$(ERROR)
	@diff tmp/call.test6 test/call/out/6
	@$(ECHO) "Case 6 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/7 1> tmp/call.test7 2>$(ERROR)
	@diff tmp/call.test7 test/call/out/7
	@$(ECHO) "Case 7 PASS!"
	@valgrind --leak-check=full ./call < test/call/in/8 1> tmp/call.test8 2>$(ERROR)
	@diff tmp/call.test8 test/call/out/8
	@$(ECHO) "Case 8 PASS!"
	@$(ECHO) "Call PASS"
	@$(ECHO)

format:
	clang-format -i include/dlist_impl.h $(wildcard src/*.cpp)

release: format
	tar -cvf release/5.tar -C include/ dlist_impl.h -C ../src call.cpp cleaner.cpp

clean:
	rm -rf tmp/*.test*
	rm -rf testDList
	rm -rf call
	rm -rf cleaner
	rm -rf release/5.tar
