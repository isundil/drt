
#include "Sphere.hpp"

Sphere::Sphere() : AMathObject()
{
  _props.addProperty(3, new PropertyValue<double>(10));
}

double Sphere::computeEquation(Camera * camera, Ray * ray) {
  double a = SQ(ray->at<double>(0)) + SQ(ray->at<double>(1)) + SQ(ray->at<double>(2));
  double b = 2 * (camera->at<double>(0) * ray->at<double>(0) + camera->at<double>(1) * ray->at<double>(1) + camera->at<double>(2) * ray->at<double>(2));
  double c = (SQ(camera->at<double>(0)) + SQ(camera->at<double>(1)) + SQ(camera->at<double>(2))) - SQ(this->at<double>(3));

  std::pair<double, double> res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  // here get_k();

  return 0;
}
