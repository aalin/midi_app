#ifndef PLAYER_HPP
#define PLAYER_HPP

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

