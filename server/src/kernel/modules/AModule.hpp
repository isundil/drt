#pragma once

#include <string>
// #include "modules/AModule.hpp"
#include "../modules/AModule.hpp"

typedef void *(*createFncPtr)();

namespace drt
{
namespace module
{
	class AModule
	{
		public:
			AModule(void *dlHandler, const std::string &name, createFncPtr fnc);
			virtual ~AModule();
	  const std::string	&getName() const;
	  AObject	*getInstance(unsigned short subModule, char *data);
		private:
			AModule();
			AModule(const AModule &);

		private:
			void *dlhandler;
			const std::string name;
			createFncPtr instanceMaker;
	};
}
}
