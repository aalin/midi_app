#include "common.hpp"

int main()
{
	MidiApp app = MidiApp::getInstance();
	CFRunLoopRun();
	return 0;
}

