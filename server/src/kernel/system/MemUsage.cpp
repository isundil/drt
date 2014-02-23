#include <iostream>
#include <fstream>
#include <map>
#include "MemUsage.hpp"

unsigned int drt::system::MemUsage::toMo(unsigned int &value, const std::string &unit)
{
	std::map<std::string, unsigned long> table;
	table["B"] = 1024L * 1024L;
	table["kB"] = 1024L;
	table["mB"] = 1;
	table["gB"] = 1L / 1024L;
	table["tB"] = 1L / (1024L * 1024L);

	if (table.find(unit) == table.end())
		return value;
	return (value /= table[unit]);
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
		toMo(value, unit);
		if (name == "MemTotal:")
			mem.second = toMo(value, unit);
		else if (name == "MemFree:")
			mem.first = toMo(value, unit);
		else if (name == "SwapTotal:")
			swap.second = toMo(value, unit);
		else if (name == "SwapFree:")
			swap.first = toMo(value, unit);
		if (mem.first != -1 && mem.second != -1 && swap.first != -1 && swap.second != -1)
			break;
	}
	mem.first = mem.second - mem.first;
	swap.first = swap.second - swap.first;
	s.close();
}

