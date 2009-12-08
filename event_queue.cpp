#include "common.hpp"

EventQueue::EventQueue()
{
	pthread_mutex_init(&_events_mutex, 0);
}

EventQueue::~EventQueue()
{
	pthread_mutex_destroy(&_events_mutex);
}

void EventQueue::addEvent(MidiEvent event)
{
	pthread_mutex_lock(&_events_mutex);
	_events.push_back(event);
	pthread_mutex_unlock(&_events_mutex);
}

void EventQueue::fireEvents(MIDIPortRef port, MIDIEndpointRef destination)
{
	pthread_mutex_lock(&_events_mutex);

	std::vector<unsigned char> buffer(256, 0);
	MIDIPacketList* packet_list = reinterpret_cast<MIDIPacketList*>(&buffer[0]);

	MIDIPacket* packet_ptr = MIDIPacketListInit(packet_list);

	for(std::vector<MidiEvent>::iterator it = _events.begin(); it != _events.end(); it++)
	{
		const MidiEvent& midi_event = *it;
		const std::vector<unsigned char>& data = midi_event.data();
		packet_ptr = MIDIPacketListAdd(packet_list, 256, packet_ptr, 0, data.size(), &data[0]);
	}

	_events.clear();

	pthread_mutex_unlock(&_events_mutex);

	MIDISend(port, destination, packet_list);
}

std::vector<MidiEvent> EventQueue::getEventsAndClear()
{
	pthread_mutex_lock(&_events_mutex);

	std::vector<MidiEvent> new_events(_events);
	_events.clear();
	pthread_mutex_unlock(&_events_mutex);

	return new_events;
}

