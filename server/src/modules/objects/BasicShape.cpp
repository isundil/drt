#include "BasicShape.hpp"

basicShape::basicShape()
{
  name = "basic_shape";
}

AObject		*basicShape::getInstance(unsigned short subModule, char *data)
{
  AObject	*ret;  

  std::cout << "coucou je suis de type " << subModule << std::endl; 
  switch (subModule)
    {
    case SPHERE:
      t_rayon	*d = data;
      ret = new Sphere(d->color, d->r);
      break;
    case CYLINDRE:
      t_rayon	*d = data;
      ret = new Cylindre(d->color, d->r);
      break;
    case CONE:
      t_angle	*d = data;
      ret = new Cone(d->color, d->a);
      break;
    case PLAN:
      ret = new Plan((char[3])data);
      break;
    default:
      break;
    }

  return ret;
}
