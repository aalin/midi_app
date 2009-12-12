#include "midi_event.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& o, const MidiEvent& midi_event)
{
	for(std::vector<unsigned char>::iterator it = midi_event.data().begin(); it != midi_event.data().end(); it++)
		o << static_cast<int>(*it) << " ";
	return o;
}
