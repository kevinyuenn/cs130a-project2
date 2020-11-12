all: project2_first.out project2_second.out

project2_first.out: hash24.cpp dict.cpp project2_first.cpp
	g++ -std=c++11 $^ -o $@

project2_second.out: hash24.cpp dict.cpp project2_second.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out dictionary.txt