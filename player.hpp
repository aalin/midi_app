#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include "midi_app.hpp"
#include "event_queue.hpp"
#include "pattern.hpp"
#include "note_generators/drummer.hpp"

class Player
{
	public:
		Player();
		void update(std::vector<MidiEvent> midi_events, MidiApp& midi_app);

	protected:
		std::map<unsigned char, std::pair<unsigned char, Pattern> > _patterns; // BCR2000-button => pattern
		int _i;

		BCR2000 _bcr;
		EventQueue _event_queue;

		NoteGenerators::Drummer _drummer;
};

#endif

