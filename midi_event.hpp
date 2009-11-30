#ifndef MIDI_EVENT_HPP
#define MIDI_EVENT_HPP

class MidiEvent
{
	public:
		MidiEvent() { }
		MidiEvent(std::vector<unsigned char> data) : _data(data) { }
		std::vector<unsigned char> data() const { return _data; }
	
	private:
		std::vector<unsigned char> _data;
};

#endif

