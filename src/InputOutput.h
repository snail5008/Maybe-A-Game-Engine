#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Debugging/Logger.h"
#include "Debugging/Formatter.h"

namespace Engine {
	namespace IO {
		std::string ReadFile(std::string filename);
	}
}