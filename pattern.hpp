#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <vector>
#include <string>

class Pattern
{
	public:
		Pattern(std::string str) : _values(valuesFromString(str)) {}
		Pattern(std::vector<unsigned char> values) : _values(values) {}
		Pattern() {}
		
		void set(std::vector<unsigned char> values) { _values = values; }
		void set(std::string str) { _values = valuesFromString(str); }

		unsigned char at(unsigned int i) const;
		unsigned int length() const { return _values.size(); }

	protected:
		std::vector<unsigned char> _values;
		std::vector<unsigned char> valuesFromString(std::string str);
};

#endif

