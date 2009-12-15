#include "scale_player.hpp"

namespace NoteGenerators
{

ScalePlayer::ScalePlayer(unsigned char channel, Scale scale)
	: _channel(channel),
	  _scale(scale)
{
	_pattern.set("100 000 000 000 000 000 000 000 100 000 100 000 000 000 100 000");
	_old_note = 0;
}

MidiEventList
ScalePlayer::getEventsAt(unsigned int position, const BCR2000& bcr)
{
	MidiEventList events;

	if(_pattern.at(position) > 128 - bcr.get(99))
	{
		unsigned char new_note = 60 + static_cast<int>((bcr.get(91) / 128.0) * 12 + 0.5);
		if(new_note != _old_note)
		{
			if(_old_note)
				events.push_back(MidiEvent::noteOff(_channel, _old_note, 100));
			events.push_back(MidiEvent::noteOn(_channel, new_note, 100));
			_old_note = new_note;
		}
	}
	else if(bcr.get(99) == 0 && _old_note)
	{
		events.push_back(MidiEvent::noteOff(_channel, _old_note, 100));
	}

	return events;
}

}
