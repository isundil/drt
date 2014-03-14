#include "BasicShape.hpp"

basicShape::basicShape(void *dlHandler, const std::string &name, createFncPtr fnc) : AModule(dlHandler, "basic_shape", fnc)
{
}

AObject		*basicShape::getInstance(unsigned short subModule, char *data)
{
  AObject	*ret;
  t_rayon	*d = (t_rayon *)data;
  t_angle	*a = (t_angle *)data;

  // std::cout << "coucou je suis de type " << subModule << std::endl; 
  switch (subModule)
    {
    case SPHERE:
      ret = new Sphere(d->color, d->r);
      break;
    case CYLINDRE:
      ret = new Cylindre(d->color, d->r);
      break;
    case CONE:
      ret = new Cone(a->color, a->a);
      break;
    case PLAN:
      ret = new Plan((int) *data);
      break;
    default:
      break;
    }

  return ret;
}
