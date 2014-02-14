#pragma once

#include <list>
#include "ISection.hpp"

namespace drt
{
namespace parser
{
class ServerSection: public ISection
{
	public:
		ServerSection();
		ServerSection(const ServerSection &);
		virtual ~ServerSection();

		virtual void addParam(const std::string &name, const std::string &value);
		virtual bool exists(const std::string &name) const;
		virtual ISection *clone() const;

		virtual unsigned short getPort() const;
		virtual unsigned int getMaxClient() const;
		bool enabled() const;

	private:
		unsigned short port;
		unsigned int maxClient;
		bool maxClient_set;
		bool noListen;
};
}
}
