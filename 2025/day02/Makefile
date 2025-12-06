compile: main.cpp solution.hpp
	g++ -o main main.cpp -g -std=c++23 -Wall -Wextra -Wpedantic

test: solution.hpp test.cpp
	g++ -o test ../../catch_amalgamated.cpp test.cpp -g -std=c++23 -Wall -Wextra -Wpedantic	

clean:
	rm -r main test main.dSYM test.dSYM
