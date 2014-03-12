#include <iostream>
#include <fstream>
#include "Scene.hpp"
#include "worker/WorkerManager.hpp"
// #include "network/Socket.hpp"

using namespace drt::render;

Scene::Scene( std::ifstream &s )
{
  // header
  char			nbModules;
  s.read(&nbModules, sizeof(char));
  char			moduleList[nbModules][20];
   for (char n = 0; n < nbModules; n++)
    {
      s.read(moduleList[n], 20 * sizeof(char));
    }
  short			x;
  short			y;
  s.read((char *)&x, sizeof(x));
  s.read((char *)&y, sizeof(y));
  unsigned int		nbObjects;
  s.read((char *)&nbObjects, sizeof(nbObjects));

  // affichage
  std::cout << "header :" << std::endl;
  std::cout << "there is " << (int) nbModules << " modules" << std::endl;
  for (int n = 0; n < nbModules; n++)
    {
      std::cout << "[" << n << "]:" << moduleList[n] << std::endl;
    }
  std::cout << "the image size is " << x << ":" << y << std::endl;
  std::cout << "there is " << nbObjects << " objects" << std::endl;

  for (short i = 0; i < nbObjects; i++)
    this->objects.push_back(parseItem(s));

  module::ModuleManager *modules = WorkerManager::getSingleton()->getModuleManager();
  // this is not finished, it needs to do the same for sub-items;
  for (auto a = this->objects->cbegin(); a != this->objects->cend(); a++)
    this->_objects.push_back(modules->getModule(moduleList[(*a).moduleID])->getInstance((*a).data));
}


t_Item	*Scene::parseItem( std::ifstream &s )
{
  // objects
  t_Item	*obj = new t_Item;
  t_Item	*tmp;

  s.read((char *) obj, sizeof(*obj));
  std::cout << "  Module #" << (int) obj->moduleID << std::endl;
  std::cout << "  There is " << (int) obj->subModule << " sub-modules" << std::endl;
  std::cout << "  Header size : " << (int) obj->headerSize << std::endl;
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
  for (int a = 0; a < obj->nbSubItem; a++)
    obj->subItems->push_back(parseItem(s));
  return (obj);
}
