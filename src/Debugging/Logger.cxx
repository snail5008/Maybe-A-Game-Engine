#include "Logger.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

#include "Formatter.h"

// mostly from https://stackoverflow.com/questions/62226043, idk
std::string Engine::Logger::GetTime() {
    auto start = std::chrono::system_clock::now();
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char tmBuff[30];
    ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);

	std::string str = std::string(tmBuff);
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

	return str;
}

void Engine::Logger::Info(std::string message) {
#ifdef _DEBUG
	std::cout << Engine::Format("[INFO #s]: #s\n", GetTime(), message);
#endif
}

void Engine::Logger::Warning(std::string message) {
#ifdef _DEBUG
	std::cout << Engine::Format("[WARNING #s]: #s\n", GetTime(), message);
#endif
}

void Engine::Logger::Error(std::string message) {
#ifdef _DEBUG
	std::cout << Engine::Format("[ERROR #s]: #s\n", GetTime(), message);
#endif
}

void Engine::Logger::FatalError(std::string message, Window* Win) {
#ifdef _DEBUG
	std::cout << Engine::Format("[FATAL ERROR #s]: #s\n", GetTime(), message);
	std::cout << "press any key to exit\n";
	Win->~Window();
	std::cin.get();
	exit(-1);
#endif
}

