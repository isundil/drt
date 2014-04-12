#include "AdvancedLight.hpp"
#include <string.h>
#include <iostream>
#include "Spot.hpp"

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
	// transparency (double coef)
	break;
      case 3:
	// reflection (double coef)
	break;
      default:
	break;
      }
    return ret;
  }

  char			*getName()
  {
    static char		*name = strdup("basic_light");
    // static char		*name = strdup("advanced_light");
    return name;
  }
}
