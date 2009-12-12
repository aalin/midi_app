#ifndef NOTE_GENERATOR_HPP
#define NOTE_GENERATOR_HPP

class NoteGenerator
{
	public:
		virtual ~NoteGenerator() { }
		virtual MidiEventList getEventsAt(unsigned int position, const BCR2000& bcr) = 0;
};

#endif

