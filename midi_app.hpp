#ifndef MIDI_APP_H
#define MIDI_APP_H

#include <CoreMIDI/MIDIServices.h>
#include "event_queue.hpp"

class Player;

class MidiApp
{
	public:
		MidiApp();

		void run();
		void update();
		void receivePacket(const MIDIPacket* packet);

		void fireEventQueue(EventQueue& event_queue);

		~MidiApp();

	protected:
		static void read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con);
		static void timerCallback(CFRunLoopTimerRef timer, void *info);

		void fireEvents();

		MIDIClientRef _midi_client;
		MIDIPortRef _midi_in;
		MIDIPortRef _midi_out;
		MIDIEndpointRef _midi_dest;

		CFRunLoopTimerRef _timer;

		EventQueue _event_queue;

		void setupInput();
		void setupOutput();

		Player* _player;
};

#endif

