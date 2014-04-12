#include "Cone.hpp"

Cone::Cone(unsigned int color, double r, double lxa, double lxi, double lya, double lyi, double lza,
	       double lzi) : AMathObject()
{
  this->color = color;
  this->r = r;
  lim.limXMax = lxa;
  lim.limXMin = lxi;
  lim.limYMax = lya;
  lim.limYMin = lyi;
  lim.limZMax = lza;
  lim.limZMin = lzi;
}

Cone::Cone(Cone &c) : AMathObject()
{
  this->color = c.getColor();
  this->r = c.getR();
  this->lim = c.getLim();
}

double		Cone::computeEquation(Camera *camera, Ray *ray)
{
  double	a;
  double	b;
  double	c;
  std::pair<double, double> res;

  a = SQ(ray->getX()) + SQ(ray->getY()) - SQ(ray->getZ()) * this->r;
  b = 2.f * (camera->getX() * ray->getX() + camera->getY() * ray->getY() - camera->getZ() * ray->getZ() * this->r);
  c = SQ(camera->getX()) + SQ(camera->getY()) - SQ(camera->getZ()) * this->r;

  double d = SQ(b) - 4 * a * c;

  res = UtilSdeg::getRoots(a, b, c);

  // std::cout << res.first << std::endl;
  // std::cout << res.second << std::endl;

  double	k = UtilSdeg::getK(res, d);
  t_pt		p;
  p.x = camera->getX() + k * ray->getX();
  p.y = camera->getY() + k * ray->getY();
  p.z = camera->getZ() + k * ray->getZ();
  if (lim.limXMax > lim.limXMin)
    {
      if (p.x < lim.limXMin || p.x > lim.limXMax)
	k = -1;
    }
  if (lim.limYMax > lim.limYMin)
    {
      if (p.y < lim.limYMin || p.y > lim.limYMax)
	k = -1;
    }
  if (lim.limZMax > lim.limZMin)
    {
      if (p.z < lim.limZMin || p.z > lim.limZMax)
	k = -1;
    }
  return k;
}

t_pt	Cone::getNormale(t_pt p, t_pt l)
{
  t_pt n;

  n.x = p.x;
  n.y = p.y;
  n.z = - p.z;

  return n;
}
