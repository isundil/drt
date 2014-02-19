#pragma once

#include <fstream>
#include <string>
#include <list>
#include <map>

namespace drt
{
namespace system
{
class CpuUsage
{
	public:
		static std::list<int>getCpuUsage();

	public: //nested class
		struct unix_stat
		{
			int user;
			int nice;
			int system;
			int idle;
		};

	private:
		static int evalLine(std::ifstream &);

		static std::map<std::string, struct unix_stat> lastData;

	private:
		CpuUsage();
};
}
}
