#include "Scene.hpp"
#include "network/Socket.hpp"

using namespace drt::render;

Scene::Scene( drt::network::Socket * s, size_t size)
{
  // header
  char			nbModules;
  read(*s, &nbModules, sizeof(char));
  char			**plop = new char[nbModules][24];
  for (char n = 0; n < nbModules; n++)
    {
      read(*s, plop[n], 24 * sizeof(*plop[n]));
    }
  short			x;
  short			y;
  read(*s, &x, sizeof(x));
  read(*s, &y, sizeof(y));
  short			nbObjects;
  read(*s, &nbObjects, sizeof(nbObjects));

  // affichage
  std::cout << "header :" << std::endl;
  std::cout << "there is " << nbModules << " modules" << std::endl;
  for (char n = 0; n < nbModules; n++)
    {
      std::cout << plop[n] << std::endl;
    }
  std::cout << "the image size is " << x << ":" << y << std::endl;
  std::cout << "there is " << nbObjects << " objects" << std::endl;

  // objects
  for (short i = 0; i < nbObjects; i++)
    {
      char		objType;
      read(*s, &objType, sizeof(objType));
      short		objSize;
      read(*s, &objSize, sizeof(objSize));
      char		nbObjMod;
      read(*s, &nbObjMod, sizeof(nbObjMod));
      void		**plip = new void[nbObjMod]*;
      for (short a = 0; a < nbObjMod; a++)
	{
	  // here I need to implement the structure.
	  //	  plip[a] = new T;
	  //	  read(*s, plip[a], objSize);
	}
    }
}
