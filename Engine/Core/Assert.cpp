#include "pch.h"
#include "Assert.h"

void _assert(bool expression, const std::string& expression_string, const std::string& filename, int line, const std::string& function_name)
{
	if (expression == false)
	{
		std::cout << "assertion failed: " << expression_string << std::endl;
		std::cout << "source: " << filename << std::endl;
		std::cout << "line: " << line << std::endl;
		std::cout << "function: " << function_name << std::endl;
		abort();
	}
}

void _assert(bool expression, const std::string& expression_string, const std::string& filename, int line, const std::string& function_name, const std::string& message)
{
	if (expression == false)
	{
		std::cout << "assertion failed: " << expression_string << std::endl;
		std::cout << message << std::endl;
		std::cout << "source: " << filename << std::endl;
		std::cout << "line: " << line << std::endl;
		std::cout << "function: " << function_name << std::endl;
		abort();
	}
}

