#include "BasicTransform.hpp"
#include <string.h>
#include <iostream>

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject		*ret = nullptr;
    t_param		*param = (t_param *) data;

    std::cout << "basic_transform:" << subModule << std::endl;

    switch (subModule)
      {
      case 1:
	ret = new Translation((double)param->x, (double)param->y, (double)param->z);
	break;
      case 2:
	ret = new Rotation((double)param->x, (double)param->y, (double)param->z);
	break;
      default:
	break;
      }
    return ret;
  }

  char			*getName()
  {
    static char		*name = strdup("basic_transform");
    return name;
  }
}
