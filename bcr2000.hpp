#ifndef BCR2000_HPP
#define BCR2000_HPP

#include <vector>

class BCR2000
{
	public:
		BCR2000();

		unsigned char get(unsigned char i) const;
		void set(unsigned char i, unsigned char v);

	protected:
		std::vector<unsigned char> _values;

		void validateValue(unsigned char val) const
		{
			if(val > 127)
				throw "i is over 127";
		}
};

#endif

