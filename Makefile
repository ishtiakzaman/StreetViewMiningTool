all: svtool

svtool: CImg.h main.cpp
	g++ main.cpp -o svtool -lX11 -lpthread -I. -O3

clean:
	rm svtool