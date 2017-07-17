#pragma once

#include "Tick.h"
#include <set>

namespace BackTest {

class TickEngine 
{
public:
	void Test(std::set<std::string>& instruments);
	Tick StrToTick(const std::string& line);
};

}