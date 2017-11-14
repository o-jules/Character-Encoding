CC = c++
CC11 = g++ --std=c++11

ifeq ($(OS), Windows_NT)
  EXE = exe
else
  EXE = out
endif

test.o: test.cpp
	$(CC11) -c test.cpp

test: test.o
	$(CC11) -o test.$(EXE) test.o

.PHONY: clean

clean:
	rm test.o test.$(EXE)
