#include "InputOutput.h"

std::string Engine::IO::ReadFile(std::string filename) {
	std::ifstream file;
	file.open(filename, std::ios::in);

	if (!file) {
		Logger::Error(Engine::Format("Could not read file '#s', the file probably doesn't exist.", filename));
		return "ERROR";
	}
	
	std::string line;
	std::stringstream contents;
	while (getline(file, line)) {
		contents << line << '\n';
	}

	file.close();

	return contents.str();
}