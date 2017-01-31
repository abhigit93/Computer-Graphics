TARGET = Run

all: ${TARGET}

Run: main.o bezcurve.o lagrange.o
	 g++ -o bin/Run main.o bezcurve.o lagrange.o -lGL -lGLU -lglut -lm

main.o: source/main.cpp include/bezcurve.h include/lagrange.h
		g++ -c source/main.cpp

bezcurve.o: source/bezcurve.cpp 
			g++ -c source/bezcurve.cpp

lagrange.o: source/lagrange.cpp
			g++ -c source/lagrange.cpp 
	
clean: 
		rm *.o bin/Run
