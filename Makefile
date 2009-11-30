LIBS = -framework CoreServices -framework CoreFoundation -framework CoreMIDI
OBJS = main.o midi_app.o
APPNAME = midi_app
OPTS = -ggdb -Wall -Wextra

default: $(OBJS)
	g++ $(OPTS) $(LIBS) -o $(APPNAME) $(OBJS)

main.o: main.cpp
	g++ -c main.cpp

midi_app.o: midi_app.cpp midi_app.hpp
	g++ -c midi_app.cpp

clean:
	rm -f $(APPNAME) *.o
