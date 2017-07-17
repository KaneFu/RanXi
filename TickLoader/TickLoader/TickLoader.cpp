// TickLoader.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "TickEngine.h"
#include <set>
#include <string>

int main()
{
	BackTest::TickEngine tickEngine;
	std::set<std::string> instruments = { "ru1709", "ru1801" };

	tickEngine.Test(instruments);

    return 0;
}

