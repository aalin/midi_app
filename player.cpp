#include "common.hpp"

Player::Player()
{
	_patterns[97] = Pattern("100 0 0 100 100 0 0 0");
}

void Player::update(std::vector<MidiEvent> midi_events)
{
	for(std::vector<MidiEvent>::iterator it = midi_events.begin();
		it != midi_events.end();
		it++)
	{
		std::vector<unsigned char> midi_data(it->data());

		if(midi_data[0] == 176)
		{
			std::cout << (int)midi_data[1] << std::endl;
			std::map<unsigned char, Pattern>::iterator it = _patterns.find(midi_data[1]);
			if(it != _patterns.end())
				std::cout << (int)it->second.at(_i) << std::endl;
		}
	}

	_i += 1;
}

