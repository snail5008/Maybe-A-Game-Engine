#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Logger.h"
#include "Formatter.h"

namespace Engine {
	namespace IO {
		std::string ReadFile(std::string filename);
	}
}