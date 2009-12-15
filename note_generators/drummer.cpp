#include "drummer.hpp"

NoteGenerators::Drummer::Drummer(unsigned char channel)
	: _channel(channel)
{
	_snare_pattern.set("000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 100 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 100 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000");
	_bass_pattern.set("100 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 100 000 000 000 000 000 000 000 100 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000");
};

MidiEventList
NoteGenerators::Drummer::getEventsAt(unsigned int position, const BCR2000& bcr)
{
	MidiEventList events;

	if(_snare_pattern.at(position) > 128 - bcr.get(89))
		events.push_back(MidiEvent::noteOn(_channel, 38, 100));

	if(_bass_pattern.at(position) > 128 - bcr.get(97))
		events.push_back(MidiEvent::noteOn(_channel, 36, 100));

	return events;
}

