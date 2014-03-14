
#include "Sphere.hpp"

Sphere::Sphere(unsigned int color, double r) : AMathObject()
{
  this->color = color;
  this->r = r;
}

double Sphere::computeEquation(Camera * camera, Ray * ray)
{
  double a = SQ(ray->getX()) + SQ(ray->getY()) + SQ(ray->getZ());
  double b = 2 * (camera->getX() * ray->getX() + camera->getY() * ray->getY() + camera->getZ() * ray->getZ());
  double c = (SQ(camera->getX()) + SQ(camera->getY()) + SQ(camera->getZ())) - SQ(this->r);
  double d = SQ(b) - 4 * a * c;

  std::pair<double, double> res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return UtilSdeg::getK(res, d);
}
