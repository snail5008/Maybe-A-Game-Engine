#pragma once

#include "../Window.h"

#include <iostream>
#include <string>
#include <chrono>
#include <cstdarg>

namespace Engine {

	namespace Logger {
		void Info(std::string message);
		void Warning(std::string message);
		void Error(std::string message);
		void FatalError(std::string message, Window* window);
		std::string GetTime();
	}
}