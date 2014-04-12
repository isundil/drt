#include "BasicShape.hpp"
#include <string.h>
#include <iostream>

basicShape::basicShape()
{
}

extern "C"
{
  AObject		*getInstance(unsigned short subModule, char *data)
  {
    AObject	*ret;
    t_rayon	*d = (t_rayon *)data;
    t_angle	*a = (t_angle *)data;

    std::cout << "basic_shape:" << subModule << std::endl;
    
    switch (subModule)
      {
      case SPHERE:
	std::cout << "initializing Sphere" << std::endl;
	ret = new Sphere(d->color, d->r);
	break;
      case CYLINDRE:
	ret = new Cylindre(d->color, d->r);
	break;
      case CONE:
	ret = new Cone(a->color, (double)a->a);
	break;
      case PLAN:
	ret = new Plan((int) *data);
	break;
      default:
	break;
      }

    return ret;
  }

  const char	*getName()
  {
    static char	*name = strdup("basic_shape");
    return name;
  }
}
