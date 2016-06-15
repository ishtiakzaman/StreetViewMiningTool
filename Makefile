all: svtool

svtool: CImg.h main.cpp
	g++ main.cpp -o svtool -lX11 -lpthread -I.

clean:
	rm svtool