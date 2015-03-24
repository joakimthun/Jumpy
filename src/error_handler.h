#pragma once

#include <string>
#include <iostream>

class ErrorHandler {
private:
public:
	inline void displayError(std::string error)
	{
		std::cout << error << std::endl;
	}
};
