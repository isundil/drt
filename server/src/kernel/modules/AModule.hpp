#pragma once

#include <string>
#include "AObject.hpp"

typedef AObject *(*createFncPtr)(int, void *);

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
	  AObject	*getInstance(unsigned short submodule, char *data);

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
