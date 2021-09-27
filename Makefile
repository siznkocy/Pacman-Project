all: compile link

test: compile link run

compile:
	g++ -c *.cpp

link:
	g++ *.o -o Main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o

run:
	Main.exe