#include "TickEngine.h"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <boost/filesystem.hpp>

namespace {
void EnumerateFiles(const std::string& baseDir, std::vector<std::string>& fileNames, bool getDir, bool leaf = true)
{
	fileNames.clear();
	boost::filesystem::path p(baseDir);
	try
	{
		if (boost::filesystem::exists(p))
		{
			if (boost::filesystem::is_directory(p))
			{
				for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(p))
				{
					if (boost::filesystem::is_directory(entry.path()))
					{
						if (getDir)
						{
							if (leaf)
							{
								fileNames.push_back(entry.path().leaf().string());
							}
							else
							{
								fileNames.push_back(entry.path().string());
							}
						}
					}
					else
					{
						if (!getDir)
						{
							if (leaf)
							{
								fileNames.push_back(entry.path().leaf().string());
							}
							else
							{
								fileNames.push_back(entry.path().string());
							}
						}
					}
				}
			}
		}
	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}
}

namespace BackTest {

void TickEngine::Test(std::set<std::string>& instruments)
{
	std::vector<std::string> fileList;
	std::vector<int> dateVec;
	EnumerateFiles("./data", fileList, true);

	for (const auto& file : fileList)
	{
		dateVec.push_back(atoi(file.c_str()));
	}
	std::sort(dateVec.begin(), dateVec.end());

	for (int date : dateVec)
	{
		std::set<Tick> ticks;
		std::shared_ptr<Tick> tickPtr;
		for (const auto& instrument : instruments)
		{
			std::ifstream ifs("./data" + instrument + ".tick");
			if (!ifs.is_open())
			{
				throw std::runtime_error("Error open " + instrument + " in " + std::to_string(date));
			}
			std::string line;
			while (std::getline(ifs, line))
			{
				ticks.insert(StrToTick(line));
			}
		}
		for (auto &tick : ticks)
		{
			// TODO: print tick
			// std::cout << tick << std::endl;
		}

	}
}

Tick TickEngine::StrToTick(const std::string & line)
{
	// TODO: parse line and save corresponding field to tick
	Tick tick;
	tick._instrument = "";
	tick._curr = 0;
	tick._vol = 0;
	tick._ask1 = 0;
	tick._askVol = 0;
	tick._bid1 = 0;
	tick._bidVol = 0;
	tick._interest = 0;
	tick._typeIndex = 0;
	tick._time = 0;
	tick._msec = 0;
	tick._turnover = 0;
	return tick;
}

}