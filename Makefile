LIBS = -framework CoreServices -framework CoreFoundation -framework CoreMIDI

default: main.o
	g++ -Wall -Wextra $(LIBS) -o midi_app main.o

main.o: main.cpp
	g++ -c main.cpp
