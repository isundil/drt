#pragma once

#include <list>

namespace drt
{
namespace module
{
	class AModule;
	class ModuleManager
	{
		public:
			ModuleManager();
			virtual ~ModuleManager();

		private:
			std::list<std::string> getFiles(const std::string &) const;
			void loadFile(const std::string &);

		private:
			std::list<AModule *> modules;
	};
}
}

