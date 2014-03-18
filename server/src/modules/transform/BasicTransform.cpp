#include "BasicTransform.hpp"
#include <string.h>

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject		*ret = nullptr;
    t_param		*param = (t_param *) data;

    switch (subModule)
      {
      case 1:
	ret = new Translation(param->x, param->y, param->z);
	break;
      case 2:
	// ret = new Rotation(param->x, param->y, param->z);
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
