#pragma once

#include <fstream>
#include <list>
#include <map>
#include "ISection.hpp"

namespace drt
{
namespace parser
{
class UnixParser
{
	public:
		UnixParser();
		virtual ~UnixParser();

		void parseFile(std::ifstream &file);
		const ISection *getSection(const std::string &name) const;
		const std::list<const ISection *> getSections() const;

	private:
		void parseLine(const std::string &line);
		void readSection(std::istringstream &line);

		ISection *section;
		std::string sectionName;
		std::map<std::string, ISection *> sections;
};
}
}

