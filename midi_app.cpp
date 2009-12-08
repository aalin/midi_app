#include "common.hpp"
#include <iostream>
#include <sstream>

MidiApp* MidiApp::instance = 0;

void MidiApp::read(const MIDIPacketList* packet_list, void* midi_app, void* src_conn_ref_con)
{
	MIDIPacket* packet = const_cast<MIDIPacket*>(packet_list->packet);
	for(unsigned int i = 0; i < packet_list->numPackets; i++)
	{
		static_cast<MidiApp*>(midi_app)->receivePacket(packet);
		packet = MIDIPacketNext(packet);
	}
}

void MidiApp::receivePacket(const MIDIPacket* packet)
{
	std::vector<unsigned char> v;
	for (int i=0; i<packet->length; i++)
	{
		v.push_back(static_cast<unsigned char>(packet->data[i]));
		std::cout << static_cast<int>(packet->data[i]) << " ";
	}
	std::cout << std::endl;

	v[1] += 1;

	MidiEvent event(v);
	_event_queue.addEvent(event);
}

void MidiApp::timerCallback(CFRunLoopTimerRef timer, void* info)
{
	if(info)
		static_cast<MidiApp*>(info)->update();
}

MidiApp::MidiApp()
	: _player(0)
{
	OSStatus status;
	if((status = MIDIClientCreate(CFSTR("MidiApp"), 0, 0, &_midi_client)))
	{
		std::cerr << "Couldn't create MIDI client, " << status << std::endl;
		std::cerr << GetMacOSStatusErrorString(status) << std::endl;
		throw "couldn't create midi client";
	}

	if((status = MIDIInputPortCreate(_midi_client, CFSTR("MidiApp Input"), MidiApp::read, this, &_midi_in)))
	{
		std::cerr << "Couldn't create midi input port, " << status << std::endl;
		std::cerr << GetMacOSStatusErrorString(status) << std::endl;
		throw "couldn't create midi output port.";
	}

	setupInput();
	setupOutput();

	_timer = CFRunLoopTimerRef();

	 CFRunLoopTimerContext context;
	 context.version = 0;
	 context.info = (void*)this;
	 context.retain = 0;
	 context.release = 0;
	 context.copyDescription = 0;
	 _timer = CFRunLoopTimerCreate(kCFAllocatorDefault, CFAbsoluteTimeGetCurrent() + 0.05, 0.05, 0, 0, MidiApp::timerCallback, &context);

	 CFRunLoopAddTimer(CFRunLoopGetMain(), _timer, kCFRunLoopCommonModes);

	 _player = new Player();
}

MidiApp::~MidiApp()
{
	MIDIClientDispose(_midi_client);
	delete _player;
}

std::string getPropertyAsString(MIDIObjectRef obj, CFStringRef property_id)
{
	CFStringRef cf_str;
	MIDIObjectGetStringProperty(obj, property_id, &cf_str);
	std::string str(CFStringGetCStringPtr(cf_str, 0));
	CFRelease(cf_str);
	return str;
}

std::string inspectMidiDevice(MIDIObjectRef obj)
{
	std::stringstream ss;
	ss << getPropertyAsString(obj, kMIDIPropertyManufacturer) << " " <<
	      getPropertyAsString(obj, kMIDIPropertyModel) << " (" <<
	      getPropertyAsString(obj, kMIDIPropertyName) << ")";
	return ss.str();
}

void MidiApp::setupInput()
{
	ItemCount num_sources = MIDIGetNumberOfSources();
	std::cout << "Midi inputs:" << std::endl;
	for(ItemCount i = 0; i < num_sources; i++)
	{
		MIDIEndpointRef src = MIDIGetSource(i);
		MIDIPortConnectSource(_midi_in, src, 0);
		std::cout << "\t" << inspectMidiDevice(src) << std::endl;
	}
}

void MidiApp::setupOutput()
{
	CFStringRef port_name = CFStringCreateWithCString(0, "Output", 0);
	MIDIOutputPortCreate(_midi_client, port_name, &_midi_out);

	std::cout << "Outputs:" << std::endl;
	for(unsigned int i=0; i < MIDIGetNumberOfDestinations(); i++)
	{
		MIDIEndpointRef dest = MIDIGetDestination(i);
		std::cout << i << "." << "\t" << inspectMidiDevice(dest) << std::endl;
	}

	if(MIDIGetNumberOfDestinations() < 1)
		throw "No MIDI destinations";

	_midi_dest = MIDIGetDestination(3);
}

void MidiApp::update()
{
	_event_queue.fireEvents(_midi_out, _midi_dest);
	if(_player)
		_player->update();
}

