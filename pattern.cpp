#include "pattern.hpp"
#include <iterator>
#include <sstream>

unsigned char Pattern::at(unsigned int i) const
{
	return _values[i % _values.size()];
}

std::vector<unsigned char> Pattern::valuesFromString(std::string str)
{
	std::vector<unsigned char> values;
	std::istringstream iss(str);
	std::copy(
		std::istream_iterator<int>(iss),
		std::istream_iterator<int>(),
		std::back_inserter<std::vector<unsigned char> >(values)
	);
	return values;
}
