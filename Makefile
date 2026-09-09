all:
	g++ main.cpp -o main -O3
	./main > mandelbrot.out
	python3 render.py

prof:
	g++ main.cpp -o main -O0 -p
	./main
	gprof ./main gmon.out > analysis.txt