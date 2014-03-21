#include <limits>
#include "CpuUsage.hpp"

using namespace drt::system;

int CpuUsage::evalLine(std::ifstream &stream)
{
	std::string cpuName;
	int ignore_value;
	struct unix_stat stats;

	unsigned int usage_sum;
	unsigned int total_sum;
	unsigned char usage_percent;

	stream >> cpuName;
	if (cpuName.substr(0, 3) != "cpu")
		return -1;
	stream >> stats.user >> stats.nice >> stats.system >> stats.idle;
	stream >> ignore_value >> ignore_value >> ignore_value >> ignore_value >> ignore_value >> ignore_value;
	if (lastData.find(cpuName) == lastData.end())
	{
		lastData[cpuName] = stats;
		return 0;
	}
	usage_sum = (stats.user - lastData[cpuName].user) + (stats.nice - lastData[cpuName].nice) + (stats.system - lastData[cpuName].system);
	total_sum = usage_sum + (stats.idle - lastData[cpuName].idle);
	usage_percent = total_sum == 0 ? 0 : ((255 * usage_sum) / total_sum);
	lastData[cpuName] = stats;
	return usage_percent;
}

std::list<int> CpuUsage::getCpuUsage()
{
	std::list<int> result;
	int current;
	std::ifstream stat("/proc/stat");

	if (!stat.is_open())
		return result;
	stat.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while ((current = evalLine(stat)) != -1)
		result.push_back(current);
	stat.close();
	return result;
}

std::map<std::string, CpuUsage::unix_stat> CpuUsage::lastData;

