#ifndef MIDI_APP_H
#define MIDI_APP_H

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

	protected:
		static MidiApp* instance;
		static void read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con);
		static void timerCallback(CFRunLoopTimerRef timer, void *info);

		MidiApp();

		MIDIClientRef _midi_client;
		MIDIPortRef _midi_in;

		CFRunLoopTimerRef _timer;
};

#endif

