#include <iostream>
#include <assert.h>
extern bool SmartPtrUnitTest();
extern bool TestContainers();
extern bool MessageControllerUnitTest();

int main() {

	assert(SmartPtrUnitTest());
	std::cout << "Pass smarter point test" << std::endl;
	assert(TestContainers());
	std::cout << "Pass container test" << std::endl;
	assert(MessageControllerUnitTest());
	std::cout << "Pass message controller test" << std::endl;
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	assert(_CrtDumpMemoryLeaks() == 0);
	std::cout << "No Memory Leak" << std::endl;

	return 0;
}
