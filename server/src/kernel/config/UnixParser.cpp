#include <iostream>
#include <sstream>
#include "UnixParser.hpp"
#include "Config.hpp"

#include "PeerSection.hpp"
#include "ServerSection.hpp"
#include "WorkerSection.hpp"

using namespace drt::parser;

UnixParser::UnixParser(): section(nullptr)
{
	sections["peers"] = new PeerSection();
	sections["server"] = new ServerSection();
	sections["worker"] = new WorkerSection();
}

UnixParser::~UnixParser()
{
	for (auto i = sections.cbegin(); i != sections.cend(); i++)
		delete (*i).second;
}

void UnixParser::readSection(std::istringstream &line)
{
	line.get();
	std::getline(line, sectionName, ']');
	if (sections.find(sectionName) == sections.end())
	{
		section = nullptr;
		std::cerr << "Warning: Invalid section name: " << sectionName << ". Ignoring section." << std::endl;
		return;
	}
	section = sections[sectionName];
}

void UnixParser::parseLine(const std::string &lineStr)
{
	std::istringstream line(lineStr);
	std::string varName;
	std::string varVal;

	while (line.peek() == ' ' || line.peek() == '\t')
		line.get();
	if (line.peek() == '[')
	{
		readSection(line);
		return;
	}
	if (section == nullptr)
		return;
	line >> varName >> varVal;
	if (varName == "")
		return;
	while (varVal[varVal.length()] == ' ')
		varVal = varVal.substr(0, varVal.length() -1);
	if (!section->exists(varName))
	{
		std::cerr << "Warning: Invalid var name \"" << varName << "\" for section " << sectionName << ". Ignoring." << std::endl;
		return;
	}
	section->addParam(varName, varVal);
}

void UnixParser::parseFile(std::ifstream &in)
{
	std::string line;
	size_t delimiter;

	while (true)
	{
		try
		{
			std::getline(in, line);
		}
		catch (std::ifstream::failure &e)
		{
			(void)e;
			return;
		}
		delimiter = line.find("#");
		if (delimiter != std::string::npos)
			line = line.substr(0, delimiter);
		parseLine(line);
	}
}

const ISection *UnixParser::getSection(const std::string &name) const
{
	try
	{
		return sections.at(name);
	}
	catch (std::exception &e)
	{
		return nullptr;
	}
}

const std::list<const ISection *> UnixParser::getSections() const
{
	std::list<const ISection *> result;

	for (auto i = sections.cbegin(); i != sections.cend(); i++)
		result.push_back((*i).second->clone());
	return result;
}

