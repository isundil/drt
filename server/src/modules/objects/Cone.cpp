#include "Cone.hpp"

Cone::Cone() : AMathObject()
{
  _props.addProerty(3, new PropertyValue<double>(10));
}

double		Cone::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->at<double>(0)) + SQ(ray->at<double>(1)) + SQ(ray->at<double>(2));
  b = 2 * (camera->at<double>(0) * ray->at<double>(0) + camera->at<double>(1) * ray->at<double>(1) - camera->at<double>(2) * ray->at<double>(2) * this->at<double>(3));
  c = SQ(camera->at<double>(0)) + SQ(camera->at<double>(1)) - SQ(camera->at<double>(2)) * this->at<double>(3);

  res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return 0;
}
