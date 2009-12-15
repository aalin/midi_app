#include <iostream>
#include "event_queue.hpp"

void EventQueue::addEvent(MidiEvent event)
{
	Mutex::Lock lock(_events_mutex);
	_events.push_back(event);
}

void EventQueue::fireEvents(MIDIPortRef port, MIDIEndpointRef destination)
{
	MidiEventList events(getEventsAndClear());

	if(events.size() == 0)
		return;

	std::vector<unsigned char> buffer(256, 0);
	MIDIPacketList* packet_list = reinterpret_cast<MIDIPacketList*>(&buffer[0]);

	MIDIPacket* packet_ptr = MIDIPacketListInit(packet_list);

	std::cout << "Firing " << events.size() << " events" << std::endl;
	for(std::vector<MidiEvent>::iterator it = events.begin(); it != events.end(); it++)
	{
		std::cout << "  Event: " << *it << std::endl;
		const MidiEvent& midi_event = *it;
		const std::vector<unsigned char>& data = midi_event.data();
		packet_ptr = MIDIPacketListAdd(packet_list, 256, packet_ptr, 0, data.size(), &data[0]);
	}

	MIDISend(port, destination, packet_list);
}

MidiEventList EventQueue::getEventsAndClear()
{
	Mutex::Lock lock(_events_mutex);

	std::vector<MidiEvent> new_events(_events);
	_events.clear();

	return new_events;
}

