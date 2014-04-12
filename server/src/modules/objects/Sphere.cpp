
#include "Sphere.hpp"

Sphere::Sphere(unsigned int color, double r, double lxa, double lxi, double lya, double lyi, double lza,
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

Sphere::Sphere(Sphere &s) :AMathObject()
{
  this->color = s.getColor();
  this->r = s.getR();
  this->lim = s.getLim();
}

double Sphere::computeEquation(Camera * camera, Ray * ray)
{
  double a = SQ(ray->getX()) + SQ(ray->getY()) + SQ(ray->getZ());
  double b = 2 * (camera->getX() * ray->getX() + camera->getY() * ray->getY() + camera->getZ() * ray->getZ());
  double c = SQ(camera->getX()) + SQ(camera->getY()) + SQ(camera->getZ()) - SQ(this->r);
  double d = SQ(b) - 4 * a * c;

  std::pair<double, double> res = UtilSdeg::getRoots(a, b, c);

  // std::cout << "res1 = " << res.first << std::endl;
  // std::cout << "res2 = " << res.second << std::endl;

  double	k = UtilSdeg::getK(res, d);
  t_pt		p;
  p.x = camera->getX() + k * ray->getX();
  p.y = camera->getY() + k * ray->getY();
  p.z = camera->getZ() + k * ray->getZ();
  if (lim.limXMax > lim.limXMin)
    {
      if (p.x < lim.limXMin || p.x > lim.limXMax)
	{
	  k = -1;
	  if (res.second > 0)
	    {
	      p.x = camera->getX() + res.second * ray->getX();
	      p.y = camera->getY() + res.second * ray->getY();
	      p.z = camera->getZ() + res.second * ray->getZ();
	      if (p.x > lim.limXMin && p.x < lim.limXMax)
		k = res.second;
	    }
	}
    }
  if (lim.limYMax > lim.limYMin)
    {
      if (p.y < lim.limYMin || p.y > lim.limYMax)
	{
	  k = -1;
	  if (res.second > 0)
	    {
	      p.x = camera->getX() + res.second * ray->getX();
	      p.y = camera->getY() + res.second * ray->getY();
	      p.z = camera->getZ() + res.second * ray->getZ();
	      if (p.y > lim.limYMin && p.y < lim.limYMax)
		k = res.second;
	    }
	}
    }
  if (lim.limZMax > lim.limZMin)
    {
      if (p.z < lim.limZMin || p.z > lim.limZMax)
	{
	  k = -1;
	  if (res.second > 0)
	    {
	      p.x = camera->getX() + res.second * ray->getX();
	      p.y = camera->getY() + res.second * ray->getY();
	      p.z = camera->getZ() + res.second * ray->getZ();
	      if (p.z > lim.limZMin && p.z < lim.limZMax)
		k = res.second;
	    }
	}
    }
  return k;
}

t_pt	Sphere::getNormale(t_pt p, t_pt l)
{
  t_pt	n;

  n.x = p.x;
  n.y = p.y;
  n.z = p.z;

  return n;
}
