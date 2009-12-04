#ifndef MIDI_EVENT_HPP
#define MIDI_EVENT_HPP

class MidiEvent
{
	public:
		MidiEvent() { }
		MidiEvent(std::vector<unsigned char> data) : _data(data) { }
		std::vector<unsigned char> data() const { return _data; }

		friend std::ostream& operator<<(std::ostream& o, const MidiEvent& midi_event);

	private:
		std::vector<unsigned char> _data;
};

#endif

