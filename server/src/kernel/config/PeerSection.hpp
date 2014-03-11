#pragma once

#include <list>
#include "ISection.hpp"

namespace drt
{
namespace parser
{
class PeerSection: public ISection
{
	public:
		PeerSection();
		PeerSection(const PeerSection &);
		virtual ~PeerSection();

		virtual void addParam(const std::string &name, const std::string &value);
		virtual bool exists(const std::string &name) const;

		virtual ISection *clone() const;

		const std::list<std::pair<std::string, unsigned short> >getPeerlist() const;
		void remPeerlist(const std::pair<std::string, unsigned short> &inf);

	private:
		std::list<std::pair<std::string, unsigned short> >peerList; //ip, port
};
}
}
