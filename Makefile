all : main

main: CImg.h main.cpp
	g++ -Dcimg_display=0 main.cpp -o svtool -lX11 -lpthread -I. 

clean:
	rm svtool