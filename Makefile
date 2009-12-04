LIBS = -framework CoreServices -framework CoreFoundation -framework CoreMIDI
OBJS = main.o midi_app.o bcr2000.o midi_event.o
APPNAME = midi_app
CCOPTS = -ggdb -Wall -Wextra

default: $(OBJS)
	g++ $(LIBS) -o $(APPNAME) $^

%.o: %.cpp %.hpp
	g++ $(CCOPTS) -c $<

clean:
	rm -f $(APPNAME) *.o
