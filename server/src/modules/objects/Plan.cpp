#include "Plan.hpp"

Plan::Plan(char color[3]): AMathObject()
{
  _props.addProperty("color", new PropertyValue<char[3]>(color));
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
