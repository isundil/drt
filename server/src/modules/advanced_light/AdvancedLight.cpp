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

    switch (subModule)
      {
      case 1:
	ret = (AObject*) new Spot();
	break;
      case 2:
	ret = new Transparency((double) *data);
	break;
      case 3:
	ret = new Reflection((double) *data);
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
