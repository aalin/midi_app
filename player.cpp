#include "player.hpp"

Player::Player()
	: _drummer(0)
{
	_patterns[82] = std::pair<unsigned char, Pattern>(68, Pattern(
		"100 000 000 000 000 000 000 000 050 000 000 000 000 000 000 000"
	)); // hihat1
	_patterns[90] = std::pair<unsigned char, Pattern>(51, Pattern(
		"100 000 000 000 000 000 000 000 000 000 000 000 050 000 000 000"
	)); // hihat2
	_patterns[98] = std::pair<unsigned char, Pattern>(59, Pattern(
		"100 000 000 000 000 000 000 000 050 000 000 000 000 000 000 000"
	)); // hihat3

	_patterns[99] = std::pair<unsigned char, Pattern>(0, Pattern("100 000 010 000 020 000 010 000 100 000 020 000 050 000 020 000")); // some synth
	_patterns[100] = std::pair<unsigned char, Pattern>(0, Pattern("100 000 010 000 020 000 010 000 100 000 020 000 050 000 020 000")); // some synth
	_patterns[101] = std::pair<unsigned char, Pattern>(0, Pattern("100 000 010 000 020 000 010 000 100 000 020 000 050 000 020 000")); // some synth
}

void Player::update(std::vector<MidiEvent> midi_events, MidiApp& midi_app)
{
	for(std::vector<MidiEvent>::iterator it = midi_events.begin();
		it != midi_events.end();
		it++)
	{
		std::vector<unsigned char> midi_data(it->data());
		if(midi_data[0] == 176)
			_bcr.set(midi_data[1], midi_data[2]);
	}

	for(std::map<unsigned char, std::pair<unsigned char, Pattern> >::iterator it = _patterns.begin();
		it != _patterns.end();
		it++)
	{
		unsigned char pattern_value = it->second.second.at(_i);
		unsigned char bcr_value = _bcr.get(it->first);
		unsigned char channel = 0;
		unsigned char velocity = 100;
		unsigned char note = it->second.first;

		if(it->first == 99) // just for synth test!
		{
			note = _bcr.get(91);
			channel = 1;
			velocity = _bcr.get(3);
		}
		else if(it->first == 100) // just for synth test!
		{
			note = _bcr.get(92);
			channel = 2;
			velocity = _bcr.get(4);
		}
		else if(it->first == 101) // just for synth test!
		{
			note = _bcr.get(93);
			channel = 3;
			velocity = _bcr.get(5);
		}

		if(bcr_value > 128 - pattern_value)
		{
//			std::cout << (int)pattern_value << std::endl;
			_event_queue.addEvent(MidiEvent::noteOn(channel, note, velocity));
		}
	}

	MidiEventList drummer_events = _drummer.getEventsAt(_i, _bcr);
	for(MidiEventList::iterator it = drummer_events.begin(); it != drummer_events.end(); it++)
		_event_queue.addEvent(*it);

	midi_app.fireEventQueue(_event_queue);

	_i += 1;
}

