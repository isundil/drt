#include "Cylindre.hpp"

Cylindre::Cylindre(unsigned int color, double r) : AMathObject()
{
  this->color = color;
  this->r = r;
}

Cylindre::Cylindre(Cylindre &c) : AMathObject()
{
  this->color = c.getColor();
  this->r = c.getR();
}

double		Cylindre::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->getX()) + SQ(ray->getY());
  b = 2 * (camera->getX() * ray->getX() + camera->getY() * ray->getY());
  c = SQ(camera->getX()) + SQ(camera->getY()) - SQ(this->r);
  double d = SQ(b) - 4 * a * c;

  res = UtilSdeg::getRoots(a, b, c);

  // std::cout << res.first << std::endl;
  // std::cout << res.second << std::endl;

  return UtilSdeg::getK(res, d);
}

t_pt	Cylindre::getNormale(t_pt p, t_pt l)
{
  t_pt n;
  
  n.x = p.x;
  n.y = p.y;
  n.z = 0;

  return n;
}
