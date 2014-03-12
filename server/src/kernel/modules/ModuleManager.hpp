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
	  AModule	*getModule(std::string &name);

		private:
			std::list<std::string> getFiles(const std::string &) const;
			void loadFile(const std::string &);

		private:
			std::list<AModule *> modules;
	};
}
}

