#include "common.hpp"
#include <iostream>

MidiApp* MidiApp::instance = 0;

void printPacketInfo(const MIDIPacket* packet) {
   double timeinsec = packet->timeStamp / (double)1e9;
   printf("%9.3lf\t", timeinsec);
   int i;
   for (i=0; i<packet->length; i++) {
      if (packet->data[i] <= 0x7f) {
         printf("%d ", packet->data[i]);
      } else {
         printf("0x%x ", packet->data[i]);
      }
   }
   printf("\n");
}

void MidiApp::read(const MIDIPacketList* packet_list, void* read_proc_ref_con, void* src_conn_ref_con)
{
	std::cout << "midi thing" << std::endl;
	MIDIPacket* packet = const_cast<MIDIPacket*>(packet_list->packet);
	for(int i = 0; i < packet_list->numPackets; i++)
	{
		printPacketInfo(packet);
		packet = MIDIPacketNext(packet);
	}
}

void MidiApp::timerCallback(CFRunLoopTimerRef timer, void* info)
{
	if(info)
		static_cast<MidiApp*>(info)->update();
}

MidiApp::MidiApp()
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

	_timer = CFRunLoopTimerRef();

	 CFRunLoopTimerContext context;
	 context.version = 0;
	 context.info = (void*)this;
	 context.retain = 0;
	 context.release = 0;
	 context.copyDescription = 0;
	 _timer = CFRunLoopTimerCreate(kCFAllocatorDefault, CFAbsoluteTimeGetCurrent() + 0.05, 0.05, 0, 0, MidiApp::timerCallback, &context);

	 CFRunLoopAddTimer(CFRunLoopGetMain(), _timer, kCFRunLoopCommonModes);
}

void MidiApp::update()
{
	std::cout << "update" << std::endl;
}

