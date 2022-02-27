#include "Formatter.h"

namespace Engine {
	std::string Format(const char* fmt...) {
		std::stringstream ss;
		va_list args;
		va_start(args, fmt);

		while (*fmt != '\0') {
			if (*fmt == '#') {
				if (*(fmt + 1) == 'i') {
					int i = va_arg(args, int);
					ss << i;
					fmt++;
				}
				else if (*(fmt + 1) == 's') {
					std::string s = va_arg(args, std::string);
					ss << s;
					fmt++;
				}
				else if (*(fmt + 1) == 'c') {
					const char* c = va_arg(args, const char*);
					ss << c;
					fmt++;
				}
				else if (*(fmt + 1) == 'f') {
					double f = va_arg(args, double);
					ss << f;
					fmt++;
				}
				else if (*(fmt + 1) == '#') {
					ss << '#';
					fmt++;
				}
				fmt++;
			}
			else {
				ss << *fmt;
				fmt++;
			}
		}
		return ss.str();
	}
}