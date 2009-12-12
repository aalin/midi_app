#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include <CoreMIDI/MIDIServices.h>
#include <pthread.h>
#include <vector>
#include "midi_event.hpp"

class EventQueue
{
	public:
		EventQueue();
		~EventQueue();
		void addEvent(MidiEvent event);
		void fireEvents(MIDIPortRef port, MIDIEndpointRef destination);

		std::vector<MidiEvent> getEventsAndClear();

	protected:
		std::vector<MidiEvent> _events;
		pthread_mutex_t _events_mutex;
};

#endif

