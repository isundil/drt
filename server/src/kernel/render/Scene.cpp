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
	delete camera;
	for (auto i = objects.cbegin(); i != objects.cend(); i++)
		delete i->second;
	::unlink(scenePath.c_str());
}

Scene::s_Item::~s_Item()
{
	delete [] data;
	delete object;
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
	std::cout << std::endl << "there is " << obj->toReceive.nbSubItem << " subItems" << std::endl;
	for (unsigned int a = 0; a < obj->toReceive.nbSubItem; a++)
		obj->subItems.push_back(parseItem(s, modules, moduleArray));

	std::string tmpStr = moduleArray[(int) obj->toReceive.moduleID];
	std::cout << "module : " << tmpStr << std::endl;
	module::AModule	*tmpModule = modules->getModule(tmpStr);
	if (tmpModule == nullptr)
		throw network::CompilFail();
	result = tmpModule->getInstance(obj->toReceive.subModule, obj->data);
	std::cout << "subModule : " << (short) obj->toReceive.subModule << std::endl;
	std::cout << "getting instance of " << tmpStr << std::endl;
	obj->object = result;
	return (obj);
}

unsigned int Scene::getHeight() const
{ return height; }

unsigned int Scene::getWidth() const
{ return width; }

unsigned int Scene::calc(WorkerManager &worker, unsigned int x, unsigned int y)
{
	double	k = -1;
	double	tmpk = k;
	unsigned int  color = 0;
	Camera	saveCamera(*camera);
	x = this->width - x;
	Ray *ray = new Ray(this->d, (double)(this->width / 2) - x, (double)(this->height / 2) - y);

	for (unsigned int i = 0; i < objects.size(); i++)
	  {
	    // objects[i]->preProcess(); // I don't think the object will need a preProcess func.
	    for (auto a = objects[i]->subItems.cbegin(); a != objects[i]->subItems.cend(); a++)
	      (*a)->object->preProcess(camera, ray);
	    tmpk = objects[i]->object->computeEquation(camera, ray);
	    if ((tmpk < k || k == -1) && tmpk >= 0)
	      {
	    	k = tmpk;
	    	color = objects[i]->object->getColor();
	      }
	  }
	(void)worker;
	delete ray;
	return color;
}

