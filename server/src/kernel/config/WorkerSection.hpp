#pragma once

#include <list>
#include "ISection.hpp"

namespace drt
{
namespace parser
{
class WorkerSection: public ISection
{
	public:
		WorkerSection();
		WorkerSection(const WorkerSection &);
		virtual ~WorkerSection();

		virtual void addParam(const std::string &name, const std::string &value);
		virtual bool exists(const std::string &name) const;
		virtual ISection *clone() const;

		virtual unsigned int getMaxThread() const;

	private:
		unsigned char maxThread;
};
}
}
