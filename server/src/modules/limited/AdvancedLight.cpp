#include "AdvancedLight.hpp"
#include <string.h>
#include <iostream>
#include "Spot.hpp"

extern "C"
{
  AObject		*getInstance(unsigned short, char *data)
  {
	return new Spot((t_param *) data);
  }

  char			*getName()
  {
    // static char		*name = strdup("basic_light");
    static char		*name = strdup("advanced_light");
    return name;
  }
}
