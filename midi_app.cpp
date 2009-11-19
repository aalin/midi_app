#include "common.hpp"
#include <iostream>

MidiApp* MidiApp::instance = 0;

void printPacketInfo(const MIDIPacket* packet) {
   double timeinsec = packet->timeStamp / (double)1e9;
   printf("%9.3lf\t", timeinsec);
   int i;
   for (i=0; i<packet->length; i++) {
      if (packet->data[i] < 0x7f) {
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
}

