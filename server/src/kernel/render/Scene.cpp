#include <iostream>
#include <fstream>
#include "Scene.hpp"
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
  int			nbObjects;
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

  // objects
  // std::list<T>	objectList;
  for (short i = 0; i < nbObjects; i++)
    {
      char		moduleID;
      s.read(&moduleID, sizeof(moduleID));
      std::cout << "  Module #" << (int) moduleID << std::endl;
      char		subModule;
      s.read(&subModule, sizeof(subModule));
      std::cout << "  There is " << (int) subModule << " sub-modules" << std::endl;
      short		headerSize;
      s.read((char *) &headerSize, sizeof(headerSize));
      std::cout << "  Header size : " << (int) headerSize << std::endl;
      int		nbSubItem;
      s.read((char *) &nbSubItem, sizeof(nbSubItem));
      std::cout << "  There is " << (int) nbSubItem << " sub-items" << std::endl;

      char	tmp[128];
      for (int a = 0; a < nbSubItem; a++)
      	{
	  s.read(tmp, headerSize);
	  std::cout << "  [" << tmp << "]" << std::endl;
      	  // have to change this, need to instanciate an Object.
      	  // here I need to implement the structure. 
	  // But what structure ? I don't know... That's kinda fun... I'm still looking for the rest of the code to try to know what is sent... Maybe I'll figure it out one day...
      	}
      // objectList.pushback(obj);
    }
}
