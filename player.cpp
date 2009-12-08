#include "common.hpp"

Player::Player()
{
	_patterns[97] = Pattern("100 20 20 00 100 0 0 0");
}

void Player::update(std::vector<MidiEvent> midi_events)
{
	for(std::vector<MidiEvent>::iterator it = midi_events.begin();
		it != midi_events.end();
		it++)
	{
		std::vector<unsigned char> midi_data(it->data());
		if(midi_data[0] == 176)
			_bcr.set(midi_data[1], midi_data[2]);
	}

	for(std::map<unsigned char, Pattern>::iterator it = _patterns.begin();
		it != _patterns.end();
		it++)
	{
		unsigned char pattern_value = it->second.at(_i);
		unsigned char bcr_value = _bcr.get(it->first);
		if(bcr_value > 128 - pattern_value)
			std::cout << (int)pattern_value << std::endl;
	}

	_i += 1;
}

