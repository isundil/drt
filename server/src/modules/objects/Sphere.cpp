
#include "Sphere.hpp"

Sphere::Sphere() : AMathObject()
{
  _props.addProperty("r", new PropertyValue<double>(10));
}

double Sphere::computeEquation(Camera * camera, Ray * ray) {
  double a = SQ(ray->at<double>("x")) + SQ(ray->at<double>("y")) + SQ(ray->at<double>("z"));
  double b = 2 * (camera->at<double>("x") * ray->at<double>("x") + camera->at<double>("y") * ray->at<double>("y") + camera->at<double>("z") * ray->at<double>("z"));
  double c = (SQ(camera->at<double>("x")) + SQ(camera->at<double>("y")) + SQ(camera->at<double>("z"))) - SQ(this->at<double>("r"));

  std::pair<double, double> res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return 0;
}
