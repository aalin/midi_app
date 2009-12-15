#ifndef SCALE_PLAYER_HPP
#define SCALE_PLAYER_HPP

#include "../note_generator.hpp"
#include "../pattern.hpp"
#include "../scale.hpp"

namespace NoteGenerators
{
	class ScalePlayer : public NoteGenerator
	{
		public:
			ScalePlayer(unsigned char channel, Scale scale);
			MidiEventList getEventsAt(unsigned int position, const BCR2000& bcr);

		protected:
			Pattern _pattern;
			const Scale _scale;
			const unsigned char _channel;

			unsigned char _old_note;
	};
}

#endif

