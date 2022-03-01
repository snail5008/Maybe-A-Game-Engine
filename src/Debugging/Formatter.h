#pragma once

#include <iostream>
#include <string>
#include <cstdarg>
#include <sstream>

namespace Engine {
	std::string Format(const char* fmt...);
}