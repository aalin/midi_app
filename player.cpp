#include "common.hpp"

Player::Player()
{
	_patterns[97] = std::pair<unsigned char, Pattern>(38, Pattern("100 000 000 000 000 000 000 000 000 000 000 000 050 000 000 000    100 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000")); // bass drum
	_patterns[89] = std::pair<unsigned char, Pattern>(54, Pattern("000 000 000 000 000 000 000 000 100 000 000 000 000 000 000 000")); // snare drum

	_patterns[82] = std::pair<unsigned char, Pattern>(71, Pattern("100 000 020 000 010 000 020 000 100 000 020 000 010 000 020 000")); // hihat1
	_patterns[90] = std::pair<unsigned char, Pattern>(73, Pattern("000 000 100 000 000 000 100 000 000 000 100 000 000 000 100 000")); // hihat2
	_patterns[98] = std::pair<unsigned char, Pattern>(74, Pattern("000 020 000 020 100 020 000 020 000 020 000 020 100 020 000 020")); // hihat3
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
		if(bcr_value > 128 - pattern_value)
		{
			std::cout << (int)pattern_value << std::endl;
			_event_queue.addEvent(MidiEvent::noteOn(0, it->second.first, 100));
		}
	}

	midi_app.fireEventQueue(_event_queue);

	_i += 1;
}

