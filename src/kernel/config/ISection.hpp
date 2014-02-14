#pragma once

#include <string>

namespace drt
{
namespace parser
{
class ISection
{
	public:
		virtual ~ISection() { };

		virtual void addParam(const std::string &name, const std::string &value) =0;
		virtual bool exists(const std::string &name) const =0;

		virtual ISection *clone() const =0;
};
}
}
