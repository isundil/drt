
#include "Sphere.hpp"

Sphere::Sphere(char color[3], double r) : AMathObject()
{
  _props.addProperty("color", new PropertyValue<char[3]>(color));
  _props.addProperty("r", new PropertyValue<double>(r));
}

double Sphere::computeEquation(Camera * camera, Ray * ray)
{
  double a = SQ(ray->at<double>("x")) + SQ(ray->at<double>("y")) + SQ(ray->at<double>("z"));
  double b = 2 * (camera->at<double>("x") * ray->at<double>("x") + camera->at<double>("y") * ray->at<double>("y") + camera->at<double>("z") * ray->at<double>("z"));
  double c = (SQ(camera->at<double>("x")) + SQ(camera->at<double>("y")) + SQ(camera->at<double>("z"))) - SQ(this->at<double>("r"));
  double d = SQ(b) - 4 * a * c;

  std::pair<double, double> res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return getK(res, d);
}
