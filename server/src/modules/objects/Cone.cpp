#include "Cone.hpp"

Cone::Cone() : AMathObject()
{
  _props.addProerty("r", new PropertyValue<double>(10));
}

double		Cone::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  // cone equ: (x * x) + (y * y) - ((z * z) / (tan(r) * tan(r))) = 0
  // TO DO: implement this 
  a = 0;
  b = 0;
  c = 0;

  res = UtilSdeg::getRoots(a, b, c);

  std::cout << res.first << std::endl;
  std::cout << res.second << std::endl;

  return 0;
}
