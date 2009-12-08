#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

class MidiEvent;

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

