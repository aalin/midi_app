#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
	public:
		Player();
		void update(std::vector<MidiEvent> midi_events);

	protected:
		std::map<unsigned char, Pattern> _patterns; // BCR2000-button => pattern
		int _i;

		BCR2000 _bcr;
};

#endif

