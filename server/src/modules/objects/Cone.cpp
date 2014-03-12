#include "Cone.hpp"

Cone::Cone(char color[3],double r) : AMathObject()
{
  _props.addProerty("color", new PropertyValue<char[3]>(color));
  _props.addProerty("r", new PropertyValue<double>(r));
}

double		Cone::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->at<double>("x")) + SQ(ray->at<double>("y")) + SQ(ray->at<double>("z"));
  b = 2 * (camera->at<double>("x") * ray->at<double>("x") + camera->at<double>("y") * ray->at<double>("y") - camera->at<double>("z") * ray->at<double>("z") * this->at<double>("r"));
  c = SQ(camera->at<double>("x")) + SQ(camera->at<double>("y")) - SQ(camera->at<double>("z")) * this->at<double>("r");

  res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return 0;
}
