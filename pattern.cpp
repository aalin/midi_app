#include "common.hpp"
#include <iterator>
#include <sstream>

unsigned char Pattern::at(unsigned int i) const
{
	return _values[(i + _values.size()) % _values.size()];
}

Pattern::Pattern(std::string str)
{
	std::istringstream iss(str);
	std::copy(
		std::istream_iterator<unsigned char>(iss),
		std::istream_iterator<unsigned char>(),
		std::back_inserter<std::vector<unsigned char> >(_values)
	);
}

