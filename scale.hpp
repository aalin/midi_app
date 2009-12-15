#ifndef SCALE_HPP
#define SCALE_HPP

#include <vector>

class Scale
{
	public:
		Scale(std::vector<unsigned int> notes);
		unsigned int degrees(int deg) const;

		static Scale fromHalfSteps(std::vector<unsigned int> intervals);
		static Scale major();

	private:
		std::vector<unsigned int> _notes;
};

#endif

