#include <iostream>
#include <assert.h>

extern bool SmartPtrUnitTest();
void main() {
	assert(SmartPtrUnitTest());
	std::cout << "Pass smarter point test" << std::endl;
	assert(_CrtCheckMemory());
	std::cout << "No Memory Leak" << std::endl;
	return;
}