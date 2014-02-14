#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <sys/dir.h>
#include <dirent.h>
#include <string>
#include <list>
#include "modules/ModuleManager.hpp"
#include "modules/AModule.hpp"

using namespace drt::module;

ModuleManager::ModuleManager()
{
	std::list<std::string> dirlist;
	std::list<std::string> fileList;
	std::string dir = std::string(MODULE_DIRS);
	size_t delimiter;

	while ((delimiter = dir.find(',')) != dir.npos)
	{
		dirlist.push_back(dir.substr(0, delimiter));
		dir = dir.substr(delimiter +1);
	}
	dirlist.push_back(dir);
	for (auto i = dirlist.cbegin(); i != dirlist.cend(); i++)
		fileList.merge(getFiles((*i)));
	for (auto i = fileList.cbegin(); i!= fileList.cend(); i++)
		loadFile(*i);
}

ModuleManager::~ModuleManager()
{
	for (auto i = modules.cbegin(); i != modules.cend(); i++)
		delete (*i);
}

std::list<std::string> ModuleManager::getFiles(const std::string &dir) const
{
	DIR *d;
	struct dirent *fileinfo;
	std::list<std::string> result;

	if ((d = ::opendir(dir.c_str())) == nullptr)
	{
		std::cerr << "Warning: cannot open directory " << dir << ": " << strerror(errno) << std::endl;
		return result;
	}
	while ((fileinfo = readdir(d)) != nullptr)
	{
		if (fileinfo->d_type != DT_REG)
			continue;
		result.push_back(dir +"/" +fileinfo->d_name);
	}
	::closedir(d);
	return result;
}

void ModuleManager::loadFile(const std::string &filename)
{
	void *handler = ::dlopen(filename.c_str(), RTLD_NOW);
	void *symName;
	void *symLoader;

	if (!handler)
	{
		std::cerr << "Warning: failed to load module file " << filename << std::endl;
		return;
	}
	symName = dlsym(handler, "getName");
	symLoader = dlsym(handler, "getInstance");
	if (symName == nullptr || symLoader == nullptr)
	{
		std::cerr << "Warning: failed to load module file " << filename << " (symbol not found)" << std::endl;
		::dlclose(handler);
		return;
	}
	std::string name = ((char *(*)())symName)();
	modules.push_back(new AModule(handler, name, (void *(*)())symLoader));
}

