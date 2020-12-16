.PHONY: test clean

p1:
	g++ -Wall src/* -o p1

test: p1
	./p1 < test/test1 > test/test.out
	diff test/test.out test/output1

clean:
	rm test/test.out p1
