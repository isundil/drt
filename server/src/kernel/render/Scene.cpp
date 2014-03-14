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
  for (int n = 0; n < nbModules; n++)
    s.read(moduleList[n], 20 * sizeof(**moduleList));
  short			x;
  short			y;
  s.read((char *)&x, sizeof(x));
  s.read((char *)&y, sizeof(y));
  short			cx;
  short			cy;
  short			cz;
  double		crx;
  double		cry;
  double		crz;
  s.read((char *)&cx, sizeof(cx));
  s.read((char *)&cy, sizeof(cy));
  s.read((char *)&cz, sizeof(cz));
  s.read((char *)&crx, sizeof(crx));
  s.read((char *)&cry, sizeof(cry));
  s.read((char *)&crz, sizeof(crz));
  this->camera = new Camera(cx, cy, cz, crx, cry, crz);
  s.read((char *)&(this->d), sizeof(this->d));
  unsigned int		nbObjects;
  s.read((char *)&nbObjects, sizeof(nbObjects));

  // affichage
  std::cout << "header :" << std::endl;
  std::cout << "there is " << (unsigned int) nbModules << " modules" << std::endl;
  for (int n = 0; n < nbModules; n++)
    std::cout << "[" << n << "]:" << moduleList[n] << std::endl;
  std::cout << "the image size is " << x << ":" << y << std::endl;
  std::cout << "camera [" << cx << "," << cy << "," << cz << "][" << crx << "," << cry << "," << crz << "]" << std::endl;
  std::cout << "d " << this->d << std::endl;
  std::cout << "there is " << nbObjects << " objects" << std::endl;

  for (unsigned int i = 0; i < nbObjects; i++)
    {
      std::cout << "objet num " << i << std::endl;
      this->objects.push_back(parseItem(s));
    }

  module::ModuleManager *modules = WorkerManager::getSingleton()->getModuleManager();
  for (auto a = this->objects.begin(); a != this->objects.end(); a++)
    {
      std::string tmpStr = moduleList[(int) (*a)->moduleID];
      std::cout << "module : " << tmpStr << std::endl;
      module::AModule	*tmpModule = modules->getModule(tmpStr);
      if (tmpModule == NULL)
	std::cout << "getModule() return NULL" << std::endl;
      std::cout << "subModule : " << (short) (*a)->subModule << std::endl;
      AObject	*tmp = tmpModule->getInstance((*a)->subModule, (*a)->data);
      std::cout << "getting instance of " << tmpStr << std::endl;
      this->_objects.push_back(tmp);
      if ((*a)->subItems)
	for (auto b = (*a)->subItems->begin(); b != (*a)->subItems->end(); b++)
	  {
	    tmpStr = moduleList[(int) (*b)->moduleID];
	    std::cout << " +-adding data for " << tmpStr << std::endl;
	    // tmp->addProperty(tmpStr, (*b)->data); // ca ca ne marche plus !
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
  // t_Item	*tmp;

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
  else
	  obj->subItems = nullptr;
  for (unsigned int a = 0; a < obj->nbSubItem; a++)
    {
      obj->subItems->push_back(parseItem(s));
    }
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

  for (auto a = this->_objects.begin(); a != _objects.end(); a++)
    {
      tmpK = (*a)->computeEquation(this->camera, ray);
      if ((tmpK < k || k == -1) && tmpK != -1)
	{
	  k = tmpK;
	  color = (*a)->getColor();
	}
    }

  (void)worker;
  std::cout << "[" << x << ", " << y << "] color is " << color << " and k is " << k << std::endl;
  return color;
}

