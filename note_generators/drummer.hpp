#ifndef DRUMMER_HPP
#define DRUMMER_HPP

#include "../note_generator.hpp"
#include "../pattern.hpp"

namespace NoteGenerators
{
	class Drummer : public NoteGenerator
	{
		public:
			Drummer(unsigned char channel);
			~Drummer();
			MidiEventList getEventsAt(unsigned int position, const BCR2000& bcr);

		protected:
			Pattern* _snare_pattern;
			Pattern* _bass_pattern;
			unsigned char _channel;
	};
}

#endif

