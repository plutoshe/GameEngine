#include <string>
#include <string.h>
#include <iostream>
#include "Vector4D.h"

bool TestVector4() {
	return true;
}

bool TestMatrix4x4() {
	return true;
}

bool TestContainers() {
	return TestVector4() && TestMatrix4x4();
}