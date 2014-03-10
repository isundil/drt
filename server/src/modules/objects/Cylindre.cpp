#include "Cylindre.hpp"

Cylindre:Cylindre() : AMathObject()
{
  _props.addProperty(3, new PropertyValue<double>(5));
}

double		Cylindre::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res

  a = SQ(ray->at<double>(0)) + SQ(ray->at<double>(1));
  b = 2 * (camera->at<double>(0) * ray->at<double>(0) + camera->at<double>(1) * ray->at<double>(1));
  c = SQ(camera->at<double>(0)) + SQ(camera->at<double>(1)) - SQ(this->at<double>(3));

  res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return 0;
}
