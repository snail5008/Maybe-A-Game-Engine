#pragma once

#include <iostream>
#include <glad/glad.h>

#include "Logger.h"
#include "Formatter.h"

#ifdef _DEBUG
#define check(fn) ClearErrors();fn;GetError(__func__, __FILE__, __LINE__)
#else
#define check(fn) fn
#endif

static void ClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GetError(const char* fn, const char* file, int line) {
	unsigned int e = glGetError();
	while (e) {
		//std::cout << "Error: " << e << " in function '" << fn << " in file '" << file << "' on line " << line << '\n';
		Engine::Logger::Error(Engine::Format("Error: #i in function #c in file #c on line #i", e, fn, file, line));
		return false;
	}
	return true;
}