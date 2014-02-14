#include <iostream>
#include <stdexcept>
#include <sstream>
#include "WorkerSection.hpp"

using namespace drt::parser;

WorkerSection::WorkerSection(): maxThread(0)
{ }

WorkerSection::WorkerSection(const WorkerSection &o): maxThread(o.maxThread)
{ }

WorkerSection::~WorkerSection()
{ }

void WorkerSection::addParam(const std::string &name, const std::string &value)
{
	std::istringstream ss;
	unsigned int tds;

	(void)name;

	ss.str(value);
	if (maxThread != 0)
	{
		std::cerr << "Warning: duplicate entry \"MaxThread\". Ignoring" << std::endl;
		return;
	}
	ss >> tds;
	maxThread = tds;
	if (maxThread == 0 || maxThread > 200)
	{
		std::cerr << "Fatal: invalid number (" << value << "). Aborting" << std::endl;
		throw std::runtime_error("Parse error");
	}
}

bool WorkerSection::exists(const std::string &name) const
{
	return name == "MaxThreads";
}

unsigned int WorkerSection::getMaxThread() const
{ return maxThread == 0 ? 4 : maxThread; }

ISection *WorkerSection::clone() const
{
	return new WorkerSection(*this);
}

