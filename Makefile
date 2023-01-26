CXX = g++ 

main: main.o
	$(CXX) main.o -o main

main.o: main.cpp matrix_2d.h matrix_3d.h
	$(CXX) -c main.cpp -o main.o

matrix_3d.h: matrix_2d.h

.PHONY: clean
clean: 
	rm -rf *.o