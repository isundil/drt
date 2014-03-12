#include "BasicShape.hpp"

IObject		*getInstance(unsigned short subModule, char *data)
{
  IObject	*ret;
  int		*r = (int *) data;

  switch (subModule)
    {
    case SPHERE:
      ret = new Sphere((double) *r);
      break;
    case CYLINDRE:
      ret = new Cylindre((double) *r);
      break;
    case CONE:
      ret = new Cone((double) *r);
      break;
    case PLAN:
      ret = new Plan();
      break;
    default:
      break;
    }

  return ret;
}

