.PHONY: all cpp_matrix.o cpp_matrix.a test gcov_report cpplint cppcheck leakscheck clean
CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
ifeq ($(OS),Darwin)
	CHECKFLAGS = -lgtest
	GCOVFLAGS = --coverage
else
	# CHECKFLAGS = -lgtest -lpthread -lrt -lm -lsubunit
	CHECKFLAGS = -lgtest -lpthread -lrt -lm
	GCOVFLAGS = -fprofile-arcs -ftest-coverage
endif

all: clean cpp_matrix.a

cpp_matrix.o: cpp_matrix.cpp
	$(CC) $(CFLAGS) -c cpp_matrix.cpp -o cpp_matrix.o

cpp_matrix.a: cpp_matrix.o
	ar rc cpp_matrix.a cpp_matrix.o
	ranlib cpp_matrix.a

test: cpp_matrix.a
	clear # delete
	$(CC) $(CFLAGS) test.cpp cpp_matrix.a $(CHECKFLAGS) -o a.out
	./a.out

gcov_report: cpp_matrix.a
	$(CC) $(CFLAGS) $(GCOVFLAGS) cpp_matrix.cpp test.cpp $(CHECKFLAGS) -o gcov_rep.out
	./gcov_rep.out
	lcov -t "gcov_rep" --no-external --output-file=coverag.info --capture --directory .
	genhtml -o ./report coverag.info
	open ./report/index.html

cpplint:
	cp ../CPPLINT.cfg CPPLINT.cfg
	cp ../cpplint.py cpplint.py
	python3 cpplint.py --filter=-runtime/references --extensions=cpp *.cpp *.h
	rm -f CPPLINT.cfg
	rm -rf cpplint.py

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=passedByValue --suppress=unmatchedSuppression --suppress=missingInclude ../src/

leakscheck:
	CK_FORK=no leaks --atExit -- ./a.out

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
	rm -rf *.cfg *.py
