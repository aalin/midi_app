#include "bcr2000.hpp"

BCR2000::BCR2000()
	: _values(128, 0)
{
}

unsigned char BCR2000::get(unsigned char i) const
{
	validateValue(i);
	return _values[i];
}

void BCR2000::set(unsigned char i, unsigned char v)
{
	validateValue(i);
	validateValue(v);

	_values[i] = v;
}

