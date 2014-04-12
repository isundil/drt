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
	ret = new Sphere(d->color, d->r, d->lxa, d->lxi, d->lya, d->lyi, d->lza, d->lzi);
	break;
      case CYLINDRE:
	ret = new Cylindre(d->color, d->r, d->lxa, d->lxi, d->lya, d->lyi, d->lza, d->lzi);
	break;
      case CONE:
	ret = new Cone(d->color, d->r, d->lxa, d->lxi, d->lya, d->lyi, d->lza, d->lzi);
	break;
      case PLAN:
	ret = new Plan(a->color, a->lxa, a->lxi, a->lya, a->lyi, a->lza, a->lzi);
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
