#pragma once

#include <utility>

namespace drt
{
namespace system
{
class MemUsage
{
	public:
		static void getMemUsage(std::pair<int, int>&mem, std::pair<int, int> &swap);

	private:
		static void toMo(unsigned long &value, const std::string &unit);
};
}
}
