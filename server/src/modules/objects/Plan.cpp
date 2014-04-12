#include "Plan.hpp"

Plan::Plan(unsigned int color): AMathObject()
{
  this->color = color;
}

Plan::Plan(Plan &p) : AMathObject()
{
  this->color = p.getColor();
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
