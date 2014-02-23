#include <iostream>
#include <fstream>
#include "MemUsage.hpp"

unsigned int drt::system::MemUsage::toMo(unsigned int &value, const std::string &unit)
{
	if (unit == "kB")
		return (value = (value / 1024));
	return value;
}

void drt::system::MemUsage::getMemUsage(std::pair<int, int> &mem, std::pair<int, int> &swap)
{
	std::ifstream s("/proc/meminfo");
	std::string name, unit;
	unsigned int value;

	mem.first = mem.second = swap.first = swap.second = -1;
	if (!s.is_open())
		return;
	while (1)
	{
		if (!(s >> name >> value >> unit))
			break;
		if (name == "MemTotal:")
			mem.second = toMo(value, unit);
		else if (name == "MemFree:")
			mem.first = toMo(value, unit);
		else if (name == "SwapTotal:")
			swap.second = toMo(value, unit);
		else if (name == "SwapFree:")
			swap.first = toMo(value, unit);
	}
	mem.first = mem.second - mem.first;
	swap.first = swap.second - swap.first;
	s.close();
}

