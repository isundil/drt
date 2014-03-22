#include "Cone.hpp"

Cone::Cone(unsigned int color,double r) : AMathObject()
{
  this->color = color;
  this->r = r;
}

double		Cone::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->getX()) + SQ(ray->getY()) + SQ(ray->getZ());
  b = 2 * (camera->getX() * ray->getX() + camera->getY() * ray->getY() - camera->getZ() * ray->getZ() * this->r);
  c = SQ(camera->getX()) + SQ(camera->getY()) - SQ(camera->getZ()) * this->r;
  double d = SQ(b) - 4 * a * c;

  res = UtilSdeg::getRoots(a, b, c);

  // std::cout << res.first << std::endl;
  // std::cout << res.second << std::endl;

  return UtilSdeg::getK(res, d);
}
