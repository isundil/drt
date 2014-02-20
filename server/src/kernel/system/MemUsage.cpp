#include <iostream>
#include <fstream>
#include "MemUsage.hpp"

void drt::system::MemUsage::toMo(unsigned int &value, const std::string &unit)
{
}

void drt::system::MemUsage::getMemUsage(std::pair<int, int> &mem, std::pair<int, int> &swap)
{
	std::ifstream s("/proc/meminfo");
	std::string name, unit;
	int value;

	mem.first = mem.second = swap.first = swap.second = -1;
	if (!s.is_open())
		return;
	while (1)
	{
		if (!(s >> name >> value >> unit))
			break;
		if (name == "MemTotal:")
			mem.second = value;
		else if (name == "MemFree:")
			mem.first = value;
		else if (name == "SwapTotal:")
			swap.second = value;
		else if (name == "SwapFree:")
			swap.first = value;
		std::cout << name << std::endl;
	}
	mem.first = mem.second - mem.first;
	swap.first = swap.second - swap.first;
	s.close();
}

