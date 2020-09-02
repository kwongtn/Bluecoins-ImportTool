#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <sstream>
#include <windows.h>
#include <cstdlib>
#include <chrono>
#include <math.h>
#include <fstream>

using ::std::cout;
using ::std::cin;
using ::std::left;
using ::std::endl;

#include "json.hpp"
using json = nlohmann::json;

using namespace std;

const int NO_INPUT_NUM = -100000;

#define USER_INPUT_STRING_RETURN \
	if(userInput == "-1234"){ \
		return 9; \
	}

#define USER_INPUT_NUMBER_RETURN \
	if(userInput == -1234){ \
		return 9; \
	}

#define USER_INPUT_NUMBER_RETURN_NULL \
	if(userInput == -1234){ \
		return; \
	}