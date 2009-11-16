#include <CoreMIDI/MIDIServices.h>
#include <iostream>
#include <vector>

class MidiApp
{
	public:
		static MidiApp& setup();
		void run();

	protected:
		static MidiApp* instance;
		static void read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con);
		MidiApp();

		MIDIClientRef _midi_client;
		MIDIPortRef _midi_in;

		CFRunLoopRef _run_loop;

		bool _running;
};

MidiApp* MidiApp::instance = 0;

void MidiApp::read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con)
{
	std::cout << "midi thing" << std::endl;
}

MidiApp& MidiApp::setup()
{
	if(instance == 0)
		instance = new MidiApp();
	return *instance;
}

MidiApp::MidiApp() : _running(false)
{
	OSStatus status;
	if(status = MIDIClientCreate(CFSTR("MidiApp"), 0, 0, &_midi_client))
	{
		std::cerr << "Couldn't create MIDI client, " << status << std::endl;
		std::cerr << GetMacOSStatusErrorString(status) << std::endl;
		throw "couldn't create midi client";
	}

	if(status = MIDIInputPortCreate(_midi_client, CFSTR("MidiApp Input"), MidiApp::read, 0, &_midi_in))
	{
		std::cerr << "Couldn't create midi input port, " << status << std::endl;
		std::cerr << GetMacOSStatusErrorString(status) << std::endl;
		throw "couldn't create midi output port.";
	}

	ItemCount num_sources = MIDIGetNumberOfSources();
	for(ItemCount i = 0; i < num_sources; i++)
	{
		MIDIEndpointRef src = MIDIGetSource(i);
		MIDIPortConnectSource(_midi_in, src, 0);
		CFStringRef name_str;
		MIDIObjectGetStringProperty(src, kMIDIPropertyName, &name_str);
		std::cout << CFStringGetCStringPtr(name_str, 0) << std::endl;
	}
}

void MidiApp::run()
{
	if(_running)
		throw "You may not call run more than once.";
	_running = true;

	_run_loop = CFRunLoopGetCurrent();
	CFRunLoopRun();
}

int main()
{
	MidiApp app(MidiApp::setup());
	app.run();
	std::cout << "Hatt baby" << std::endl;
	return 0;
}

