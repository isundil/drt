#include "BasicShape.hpp"

basicShape::basicShape(void *dlHandler, const std::string &name, createFncPtr fnc) : AModule(dlHandler, name, fnc)
{
}

AObject		*basicShape::getInstance(unsigned short subModule, char *data)
{
  AObject	*ret;
  t_rayon	*d = (t_rayon *)data;
  t_angle	*a = (t_angle *)data;
  char		c[3];

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
      c[0] = data[0];
      c[1] = data[1];
      c[2] = data[2];
      ret = new Plan(c);
      break;
    default:
      break;
    }

  return ret;
}

const std::string	&basicShape::getName() const {
  return "basic_shape";
}
