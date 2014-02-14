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

