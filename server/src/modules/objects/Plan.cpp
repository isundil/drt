#include "Plan.hpp"

Plan::Plan(unsigned int color): AMathObject()
{
  _props.addProperty("color", new PropertyValue<unsigned int>(color));
}

double		Plan::computeEquation(Camera *camer, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double>	res;

  // TO DO: implement this

  return 0;
}
