#include "BasicLight.hpp"
#include <string.h>
#include <iostream>
#include "Spot.hpp"

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject		*ret = nullptr;

    std::cout << "basic_light:" << subModule << std::endl;
    switch (subModule)
      {
      case 1:
	std::cout << "initializing Spot" << std::endl;
	ret = (AObject*) new BasicSpot();
	break;
      default:
	break;
      }
    return ret;
  }

  char			*getName()
  {
    static char		*name = strdup("basic_light");
    return name;
  }
}
