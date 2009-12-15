#include "scale.hpp"
#include <boost/assign/list_of.hpp>

Scale Scale::major()
{
	return Scale::fromHalfSteps(
		boost::assign::list_of(2)(2)(1)(2)(2)(2)(1)
	);
}

Scale Scale::fromHalfSteps(std::vector<unsigned int> intervals)
{
	std::vector<unsigned int> notes(1, 0);
	for(unsigned int i = 0; i < intervals.size() - 1; i++)
		notes.push_back((notes.back() + i) % 12);
	return Scale(notes);
}

Scale::Scale(std::vector<unsigned int> notes)
	: _notes(notes)
{ }

// modulus as in Ruby
int mod(int a, int b)
{
	while(a < 0) a += b;
	return a % b;
}

unsigned int Scale::degrees(int deg) const
{
	return _notes[mod(deg, _notes.size())];
}

