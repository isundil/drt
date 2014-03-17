#include "BasicTransform.hpp"

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject		*ret;
    switch (subModule)
      {
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
