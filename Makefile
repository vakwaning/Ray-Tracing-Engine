ray1: ray_project1.o
	g++ -std=c++17 -Wall -Wextra -Werror -o ray1 ray_project1.o

ray_project1.o: ray_project1.cpp ray_project1.hpp
	g++ -std=c++17 -Wall -Wextra -Werror -c ray_project1.cpp -o ray_project1.o

clean:
	rm ray1 ray_project1.o