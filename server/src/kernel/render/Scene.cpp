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
	for (int n = 0; n < nbModules; n++)
	  std::cout << moduleList[n] << std::endl;
	//reading scene header (details)
	s.read((char *)&data, sizeof(data));
	//reading objects
	for (unsigned int i = 0; i < data.nbObjects; i++)
	  {
	    std::cout << "Item {" << std::endl;
		this->objects[i] = (parseItem(s, modules, moduleList));
	    std::cout << "}" << std::endl;
	  }
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

Scene::Scene(Scene &s) : scenePath(s.getPath()) {
  height = s.getHeight();
  width = s.getWidth();
  camera = (Camera *) s.getCamera()->clone();
  d = s.getD();
  id = s.getId();
  std::map<unsigned int, t_Item *> tmp = s.getObjects();
  for (auto a = tmp.cbegin(); a != tmp.cend(); a++) {
    t_Item *obj = new t_Item();
    obj->toReceive = (*a).second->toReceive;
    obj->data = (*a).second->data;
    for (auto i = (*a).second->subItems.cbegin(); i != (*a).second->subItems.cend(); i++) {
      t_Item *obj2 = new t_Item();
      obj2->toReceive = (*i)->toReceive;
      obj2->data = (*i)->data;
      obj2->object = (*i)->object->clone();
      if (obj2->object->getX() != (*i)->object->getX())
	std::cout << "difference !!! (getX)" << std::endl;
      if (obj2->object->getY() != (*i)->object->getY())
	std::cout << "difference !!! (getY)" << std::endl;
      if (obj2->object->getZ() != (*i)->object->getZ())
	std::cout << "difference !!! (getZ)" << std::endl;
      if (obj2->object->getColor() != (*i)->object->getColor())
	std::cout << "difference !!! (getColor)" << std::endl;
      obj->subItems.push_back(obj2);
    }
    obj->object = (*a).second->object->clone();
    this->objects[(*a).first] = obj;
  }
}

Scene	*Scene::clone() {
  return new Scene(*this);
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
	// delete [] data;
	delete object;
	for (auto i = subItems.cbegin(); i != subItems.cend(); i++)
		delete (*i);
}

Scene::t_Item	*Scene::parseItem( std::ifstream &s, module::ModuleManager *modules, std::map<unsigned int, char[20]>moduleArray)
{
	t_Item	*obj = new t_Item();
	AObject	*result;

	s.read((char *) &(obj->toReceive), sizeof(obj->toReceive));
	if (obj->toReceive.headerSize > 0)
	{
		// std::cout << "+--";
		obj->data = new char[obj->toReceive.headerSize];
		if (s.read(obj->data, obj->toReceive.headerSize));
			// std::cout << "  data contain [" << (char *) obj->data << "]" << std::endl;
	}
	std::string tmpStr = moduleArray[(int) obj->toReceive.moduleID];
	std::cout << "module : [" << tmpStr << "] (" << (int)obj->toReceive.moduleID << ")" << std::endl;
	std::cout << "subModule : " << (short) obj->toReceive.subModule << std::endl;
	std::cout << std::endl << "there is " << obj->toReceive.nbSubItem << " subItems" << std::endl
	  ;
	for (unsigned int a = 0; a < obj->toReceive.nbSubItem; a++)
	  {
	    std::cout << "SubItem [" << std::endl;
		obj->subItems.push_back(parseItem(s, modules, moduleArray));
	    std::cout << "]" << std::endl;
	  }

	module::AModule	*tmpModule = modules->getModule(tmpStr);
	if (tmpModule == nullptr)
	  {
	    // std::cout << "tmpModule == nullptr" << std::endl;
		throw network::CompilFail();
	  }
	// std::cout << "getInstance" << std::endl;
	result = tmpModule->getInstance(obj->toReceive.subModule, obj->data);
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

unsigned int Scene::calc(WorkerManager &, unsigned int x, unsigned int y)
{
	double	k = -1;
	double	tmpk = k;
	unsigned int  color = 0;
	Camera	saveCamera(*camera);
	t_Item	*lastFound = nullptr;

	x = this->width - x;
	Ray *ray = new Ray(this->d, (double)(this->width / 2) - x, (double)(this->height / 2) - y);

	for (auto i = objects.cbegin(); i != objects.cend(); i++)
	  {
	    saveCamera.reset();
	    ray->reset();
	    // (*i).second->object->preProcess(); // I don't think the object will need a preProcess func.
	    for (auto a = (*i).second->subItems.cbegin(); a != (*i).second->subItems.cend(); a++)
	      (*a)->object->preProcess(&saveCamera, ray);
	    tmpk = (*i).second->object->computeEquation(&saveCamera, ray);
	    if ((tmpk < k || k == -1) && tmpk >= 0)
	      {
	    	k = tmpk;
	    	color = (*i).second->object->getColor();
		lastFound = (*i).second;
	      }
	  }
	if (lastFound != nullptr)
	  for (auto it = objects.cbegin(); it != objects.cend(); it++)
	    color = (*it).second->object->postProcess(this, &saveCamera, ray, lastFound->object, k, color);
	
	delete ray;
	return color;
}

void Scene::setId(unsigned short _i)
{ id = _i; }

unsigned short Scene::getId() const
{ return id; }

const std::string Scene::getPath() const
{ return scenePath; }

