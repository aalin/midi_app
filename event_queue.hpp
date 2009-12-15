#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include <CoreMIDI/MIDIServices.h>
#include <vector>
#include "midi_event.hpp"
#include "mutex.hpp"

class EventQueue
{
	public:
		void addEvent(MidiEvent event);
		void fireEvents(MIDIPortRef port, MIDIEndpointRef destination);

		MidiEventList getEventsAndClear();

	protected:
		MidiEventList _events;
		Mutex _events_mutex;
};

#endif

