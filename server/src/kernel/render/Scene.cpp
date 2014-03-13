#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Scene.hpp"
// #include "network/Socket.hpp"

using namespace drt::render;

Scene::Scene( std::ifstream &s, const std::string &_scenePath ): scenePath(_scenePath)
{
  // header
  char			nbModules;
  s.read(&nbModules, sizeof(nbModules));
  char			moduleList[nbModules][20];
  for (char n = 0; n < nbModules; n++)
    s.read(moduleList[n], 20 * sizeof(**moduleList));
  short			x;
  short			y;
  s.read((char *)&x, sizeof(x));
  s.read((char *)&y, sizeof(y));
  unsigned int		nbObjects;
  s.read((char *)&nbObjects, sizeof(nbObjects));

  // affichage
  std::cout << "header :" << std::endl;
  std::cout << "there is " << (unsigned int) nbModules << " modules" << std::endl;
  for (int n = 0; n < nbModules; n++)
    std::cout << "[" << n << "]:" << moduleList[n] << std::endl;
  std::cout << "the image size is " << x << ":" << y << std::endl;
  std::cout << "there is " << nbObjects << " objects" << std::endl;

  for (short i = 0; i < nbObjects; i++)
    this->objects.push_back(parseItem(s));

  module::ModuleManager *modules = WorkerManager::getSingleton()->getModuleManager();
  for (auto a = this->objects.begin(); a != this->objects.end(); a++)
    {
      std::string tmpStr = moduleList[(*a)->moduleID];
      AObject	*tmp = modules->getModule(tmpStr)->getInstance((*a)->subModule, (*a)->data);
      std::cout << "getting instance of " << tmpStr << std::endl;
      this->_objects.push_back(tmp);
      for (auto b = (*a)->subItems->begin(); b != (*a)->subItems->end(); b++)
	{
	  tmpStr = moduleList[(*b)->moduleID];
	  std::cout << " +-adding data for " << tmpStr << std::endl;
	  tmp->addProperty(tmpStr, (*b)->data);
	}
    }
	width = y;
	height = x;
}

Scene::~Scene()
{
	::unlink(scenePath.c_str());
}

t_Item	*Scene::parseItem( std::ifstream &s )
{
  // objects
  t_Item	*obj = new t_Item;
  t_Item	*tmp;

  // s.read((char *) obj, sizeof(*obj));
  s.read((char *) &(obj->moduleID), sizeof(obj->moduleID));
  std::cout << "  Module #" << (int) obj->moduleID << std::endl;
  s.read((char *) &(obj->subModule), sizeof(obj->subModule));
  std::cout << "  There is " << (int) obj->subModule << " sub-modules" << std::endl;
  s.read((char *) &(obj->headerSize), sizeof(obj->headerSize));
  std::cout << "  Header size : " << (int) obj->headerSize << std::endl;
  s.read((char *) &(obj->nbSubItem), sizeof(obj->nbSubItem));
  std::cout << "  There is " << (int) obj->nbSubItem << " sub-items" << std::endl;
  if (obj->headerSize > 0)
    {
      std::cout << "+--";
      obj->data = new char[obj->headerSize];
      if (s.read(obj->data, obj->headerSize))
  	std::cout << "  data contain [" << (char *) obj->data << "]" << std::endl;
    }
  std::cout << std::endl;
  if (obj->nbSubItem > 0)
    obj->subItems = new std::list<t_Item *>;
  // for (int a = 0; a < obj->nbSubItem; a++)
  //   obj->subItems->push_back(parseItem(s));
  return (obj);
}

unsigned int Scene::getHeight() const
{ return height; }

unsigned int Scene::getWidth() const
{ return width; }

