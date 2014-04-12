#include "AdvancedLight.hpp"
#include <string.h>
#include <iostream>
#include "Spot.hpp"
#include "Transparency.hpp"
#include "Reflection.hpp"

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject		*ret = nullptr;
    double		*d = (double *) data;

    std::cout << "advanced_light:" << subModule << std::endl;

    switch (subModule)
      {
      case 1:
	ret = (AObject*) new Spot();
	break;
      case 2:
	ret = (AObject*) new Transparency((double) *d);
	break;
      case 3:
	ret = (AObject*) new Reflection((double) *d);
	break;
      default:
	break;
      }
    return ret;
  }

  char			*getName()
  {
    // static char		*name = strdup("basic_light");
    static char		*name = strdup("advanced_light");
    return name;
  }
}
