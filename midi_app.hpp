#ifndef MIDI_APP_H
#define MIDI_APP_H

class MidiEvent;

class MidiApp
{
	public:
		static MidiApp& getInstance()
		{
			if(instance == 0)
				instance = new MidiApp();
			return *instance;
		}

		void run();
		void update();
		void receivePacket(const MIDIPacket* packet);

		~MidiApp();

	protected:
		static MidiApp* instance;
		static void read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con);
		static void timerCallback(CFRunLoopTimerRef timer, void *info);

		void fireEvents();

		MidiApp();

		MIDIClientRef _midi_client;
		MIDIPortRef _midi_in;
		MIDIPortRef _midi_out;
		MIDIEndpointRef _midi_dest;

		CFRunLoopTimerRef _timer;

		std::vector<MidiEvent> _events;

		void setupInput();
		void setupOutput();
};

#endif

