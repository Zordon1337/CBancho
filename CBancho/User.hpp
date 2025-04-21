#pragma once
#include "Includes.h"
struct UserLogin {
	std::string username;
	std::string password;
	std::string build;
	int UtcOffset;
	bool DisplayCityLocation;
};