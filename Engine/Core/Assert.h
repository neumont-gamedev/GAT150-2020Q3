#pragma once

#ifndef NDEBUG
	#define ASSERT(expression) _assert((expression), #expression, __FILE__, __LINE__, __func__)
	#define ASSERT_MSG(expression, message) _assert((expression), #expression, __FILE__, __LINE__, __func__, message)
#else
	#define ASSERT(expression) ((void)0)
	#define ASSERT_MSG(expression, message) ((void)0)
#endif

void _assert(bool expression, const std::string& expression_string, const std::string& filename, int line, const std::string& function_name);
void _assert(bool expression, const std::string& expression_string, const std::string& filename, int line, const std::string& function_name, const std::string& message);

