#ifndef MIDI_EVENT_HPP
#define MIDI_EVENT_HPP

class MidiEvent
{
	public:
		enum Command {
			ON = 0x90,  // Note on
			OFF = 0x80, // Note off
			PA = 0xa0,  // Polyphonic aftertouch
			CC = 0xb0,  // Control change
			PC = 0xc0,  // Program change
			CA = 0xd0,  // Channel aftertouch
			PB = 0xe0   // Pitch bend
		};

		MidiEvent() { }
		MidiEvent(std::vector<unsigned char> data) : _data(data) { }
		std::vector<unsigned char> data() const { return _data; }

		friend std::ostream& operator<<(std::ostream& o, const MidiEvent& midi_event);

		static MidiEvent noteOn(unsigned char channel, unsigned char note, unsigned char velocity)
		{
			return message(ON | channel, note, velocity);
		}

		static MidiEvent noteOff(unsigned char channel, unsigned char note, unsigned char velocity)
		{
			return message(OFF | channel, note, velocity);
		}

		// TODO: Implement more messages

		static MidiEvent message(unsigned char a, unsigned char b)
		{
			std::vector<unsigned char> v;
			v.push_back(a);
			v.push_back(b);
			return MidiEvent(v);
		}

		static MidiEvent message(unsigned char a, unsigned char b, unsigned char c)
		{
			std::vector<unsigned char> v;
			v.push_back(a);
			v.push_back(b);
			v.push_back(c);
			return MidiEvent(v);
		}

	private:
		std::vector<unsigned char> _data;
};

#endif

