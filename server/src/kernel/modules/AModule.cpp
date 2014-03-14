#include <dlfcn.h>
#include "modules/AModule.hpp"

using namespace drt::module;

AModule::AModule(void *_handler, const std::string &_name, createFncPtr ptr): dlhandler(_handler), name(_name), instanceMaker(ptr)
{
}

AModule::~AModule()
{
	dlclose(dlhandler);
}

const std::string	&AModule::getName() const
{
  return name;
}


#include <iostream>
AObject	*AModule::getInstance(unsigned short submodule, char *data)
{
	return instanceMaker(submodule, data);
}
