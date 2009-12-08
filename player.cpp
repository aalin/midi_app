#include "common.hpp"

Player::Player()
{
	_patterns[97] = Pattern("100 0 0 100 100 0 0 0");
}

void
Player::update()
{
	std::cout << (int)_patterns[97].at(_i) << std::endl;
//	std::cout << "midi app" << std::endl;

	_i += 1;
}

