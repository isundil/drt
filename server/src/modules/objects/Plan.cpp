#include "Plan.hpp"

Plan::Plan(unsigned int color, double lxa, double lxi, double lya, double lyi, double lza,
	       double lzi) : AMathObject()
{
  this->color = color;
  lim.limXMax = lxa;
  lim.limXMin = lxi;
  lim.limYMax = lya;
  lim.limYMin = lyi;
  lim.limZMax = lza;
  lim.limZMin = lzi;
}

Plan::Plan(Plan &p) : AMathObject()
{
  this->color = p.getColor();
  this->lim = p.getLim();
}

double		Plan::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  double	k = -1;

  if (camera->getZ() != 0 && ray->getZ() != 0)
    k = - camera->getZ() / ray->getZ();
  else
    k = 0;

  t_pt		p;
  p.x = camera->getX() + k * ray->getX();
  p.y = camera->getY() + k * ray->getY();
  p.z = camera->getZ() + k * ray->getZ();
  if (lim.limXMax > lim.limXMin)
    if (p.x < lim.limXMin || p.x > lim.limXMax)
      k = -1;
  if (lim.limYMax > lim.limYMin)
    if (p.y < lim.limYMin || p.y > lim.limYMax)
      k = -1;  

  return k;
}

t_pt	Plan::getNormale(t_pt p, t_pt l)
{
  t_pt	n;

  n.x = 0;
  n.y = 0;
  n.z = 100;
  if (l.z < p.z)
    n.z = -100;
  return n;
}
