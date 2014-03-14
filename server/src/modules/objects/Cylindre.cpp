#include "Cylindre.hpp"

Cylindre::Cylindre(unsigned int color, double r) : AMathObject()
{
  _props.addProperty("color", new PropertyValue<unsigned int>(color));
  _props.addProperty("r", new PropertyValue<double>(r));
}

double		Cylindre::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->at<double>("x")) + SQ(ray->at<double>("y"));
  b = 2 * (camera->at<double>("x") * ray->at<double>("x") + camera->at<double>("y") * ray->at<double>("y"));
  c = SQ(camera->at<double>("x")) + SQ(camera->at<double>("y")) - SQ(this->at<double>("r"));
  double d = SQ(b) - 4 * a * c;

  res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return UtilSdeg::getK(res, d);
}
