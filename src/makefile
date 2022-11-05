CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror
GTEST = -lgtest

HEADERS =\
	matrix.h\
	slau.h

SOURCES =\
	main.cpp\
	matrix.cpp\
	slau.cpp

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LFLAGS = -lpthread
	OPEN = -xdg-open
else
	OPEN = -open
endif

APP = sle_solve

all : test build

build : $(APP)

demo : build
	./$(APP) ../data-samples/ex*

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(APP) : main.o slau.o matrix.o
	$(CC) $^ -o $@ $(LFLAGS)

test : tests

tests : tests.o matrix.o slau.o
	$(CC) $(CFLAGS) $^ $(GTEST) $(LFLAGS) -o $@.out
	./$@.out

style :
	@clang-format -n --Werror *.h --style=Google --ferror-limit=3
	@clang-format -n --Werror *.cpp --style=Google --ferror-limit=3

cppcheck :
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression $(HEADERS) $(SOURCES)

mem : clean tests
ifeq ($(OS), Linux)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./tests.out
else
	CK_FORK=no leaks --atExit -- ./tests.out
endif

gcov : gcov_report

gcov_report : clean
	$(MAKE) CFLAGS="$(CFLAGS) --coverage" LFLAGS="$(LFLAGS) --coverage" tests
	lcov -t tests.out -o test.info -c -d . --no-external
	genhtml -o report test.info
	$(OPEN) report/index.html

clean : clean_report
	$(RM) *.o *.out $(APP)

clean_report :
	$(RM) -rf *.gcda *.gcno *.info *.gch report

rebuild : clean all
