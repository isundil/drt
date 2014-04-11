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

  std::cout << "je suis une conne d'angle: " << this->r << std::endl;

  a = SQ(ray->getX()) + SQ(ray->getY()) - SQ(ray->getZ()) * this->r;
  b = 2.f * (camera->getX() * ray->getX() + camera->getY() * ray->getY() - camera->getZ() * ray->getZ() * this->r);
  c = SQ(camera->getX()) + SQ(camera->getY()) - SQ(camera->getZ()) * this->r;

  double d = SQ(b) - 4 * a * c;

  res = UtilSdeg::getRoots(a, b, c);

  // std::cout << res.first << std::endl;
  // std::cout << res.second << std::endl;

  return UtilSdeg::getK(res, d);
}

t_pt	Cone::getNormale(t_pt p, t_pt l)
{
  t_pt n;

  n.x = p.x;
  n.y = p.y;
  n.z = - p.z;

  return n;
}
