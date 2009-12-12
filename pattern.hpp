#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <vector>
#include <string>

class Pattern
{
	public:
		Pattern(std::string str);
		Pattern(std::vector<unsigned char> values) : _values(values) {}
		Pattern() {}
		unsigned char at(unsigned int i) const;
		unsigned int length() const { return _values.size(); }

	protected:
		std::vector<unsigned char> _values;
};

#endif

