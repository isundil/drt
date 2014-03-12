#pragma once

#include <string>

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
