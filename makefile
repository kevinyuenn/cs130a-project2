all: project2_first.out project2_second.out

project2_first.out: <list of .cpp files required for project2_first.out>
	g++ -std=c++11 $^ -o $@

project2_second.out: <list of .cpp files reuired for project2_second.out>
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out