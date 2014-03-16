#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Scene.hpp"
#include "network/NetworkPacket.hpp"

using namespace drt::render;

Scene::Scene( std::ifstream &s, const std::string &_scenePath ): scenePath(_scenePath)
{
	// header
	char			nbModules;
	std::map<unsigned int, char [20]>moduleList;
	module::ModuleManager *modules = WorkerManager::getSingleton()->getModuleManager();
	t_metadata data;

	//reading scene metadata (modules)
	s.read(&nbModules, sizeof(nbModules));
	for (int n = 0; n < nbModules; n++)
		s.read(moduleList[n], 20);
	//reading scene header (details)
	s.read((char *)&data, sizeof(data));
	//reading objects
	for (unsigned int i = 0; i < data.nbObjects; i++)
		this->objects[i] = (parseItem(s, modules, moduleList));
	//setting data
	this->camera = new Camera(data.camera_x, data.camera_y, data.camera_z, data.camera_rx, data.camera_ry, data.camera_rz);
	width = data.width;
	height = data.height;
	d = data.d;

	// affichage / debug
	std::cout << "header :" << std::endl;
	std::cout << "there is " << (unsigned int) nbModules << " modules" << std::endl;
	for (int n = 0; n < nbModules; n++)
		std::cout << "[" << n << "]:" << moduleList[n] << std::endl;
	std::cout << "the image size is " << data.width << ":" << data.height << std::endl <<
		"camera [" << data.camera_x << "," <<
		data.camera_y << "," << data.camera_z << "][" <<
		data.camera_rx << "," << data.camera_ry << "," <<
		data.camera_rz << "]" << std::endl <<
		"d " << this->d << std::endl <<
		"there is " << data.nbObjects << " objects" << std::endl;
}

Scene::~Scene()
{
	::unlink(scenePath.c_str());
}

Scene::t_Item	*Scene::parseItem( std::ifstream &s, module::ModuleManager *modules, std::map<unsigned int, char[20]>moduleArray)
{
	t_Item	*obj = new t_Item();
	AObject	*result;

	s.read((char *) &(obj->toReceive), sizeof(obj->toReceive));
	if (obj->toReceive.headerSize > 0)
	{
		std::cout << "+--";
		obj->data = new char[obj->toReceive.headerSize];
		if (s.read(obj->data, obj->toReceive.headerSize))
			std::cout << "  data contain [" << (char *) obj->data << "]" << std::endl;
	}
	std::cout << std::endl;
	for (unsigned int a = 0; a < obj->toReceive.nbSubItem; a++)
		obj->subItems.push_back(parseItem(s, modules, moduleArray));

	std::string tmpStr = moduleArray[(int) obj->toReceive.moduleID];
	std::cout << "module : " << tmpStr << std::endl;
	module::AModule	*tmpModule = modules->getModule(tmpStr);
	if (tmpModule == nullptr)
		throw network::CompilFail();
	result = tmpModule->getInstance(obj->toReceive.subModule, obj->data);
	if (tmpModule == NULL)
		std::cout << "getModule() return NULL" << std::endl;
	std::cout << "subModule : " << (short) obj->toReceive.subModule << std::endl;
	std::cout << "getting instance of " << tmpStr << std::endl;
	obj->object = result;
	return (obj);
}

unsigned int Scene::getHeight() const
{ return height; }

unsigned int Scene::getWidth() const
{ return width; }

void Scene::copy_bufs(unsigned char dest[4], unsigned char src[3])
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = 255;
}

unsigned int Scene::calc(WorkerManager &worker, unsigned int x, unsigned int y)
{
	double	k = -1;
	double	tmpK = k;
	unsigned int  color = 0;
	Ray		*ray = new Ray(this->d, this->width / 2 - x, this->height / 2 -y);

	/*
	for (auto a = objects.begin(); a != objects.end(); a++)
	{
		tmpK = (*a).second->object->computeEquation(camera, ray);
		if ((tmpK < k || k == -1) && tmpK != -1)
		{
			k = tmpK;
			color = (*a).second->object->getColor();
		}
	}

	(void)worker;
	std::cout << "[" << x << ", " << y << "] color is " << color << " and k is " << k << std::endl;
	*/
	return 0x1155ee;
	return color;
}

