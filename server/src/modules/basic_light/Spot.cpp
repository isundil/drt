#include <cmath>
#include <iostream>
#include "Spot.hpp"
#include "Scene.hpp"

Spot::Spot() {
  x = 0.f;
  y = 0.f;
  z = 0.f;
}

Spot::Spot(Spot &s) {
  x = 0.f;
  y = 0.f;
  z = 0.f;
}

void		Spot::normalize(t_pt *a) {
  double	r = sqrt(SQ(a->x) + SQ(a->y) + SQ(a->z));

  a->x = a->x / r;
  a->y = a->y / r;
  a->z = a->z / r;
}

unsigned int	Spot::applyLight(double cosa, unsigned int color) {
  unsigned int	r;
  unsigned int	g;
  unsigned int	b;
  unsigned int	tmpcolor = color;

  b = tmpcolor & 0x0000FF;
  tmpcolor = tmpcolor >> 8;
  g = tmpcolor & 0x0000FF;
  tmpcolor = tmpcolor >> 8;
  r = tmpcolor & 0x0000FF;

  r = cosa * r;
  if (r > 255)
    r = 255;
  g = cosa * g;
  if (g > 255)
    g = 255;
  b = cosa * b;
  if (b > 255)
    b = 255;

  tmpcolor = r;
  tmpcolor = tmpcolor << 8;
  tmpcolor += g;
  tmpcolor = tmpcolor << 8;
  tmpcolor += b;
  return tmpcolor;
} 

void		Spot::applyRotation(t_pt *n, AObject *rot)
{
  t_pt		tmp = *n;
  double	_cos = cos(- rot->getZ());
  double	_sin = sin(- rot->getZ());
  double	x;
  double	y;
  double	z;

  x = tmp.x * _cos - tmp.y * _sin;
  y = tmp.x * _sin + tmp.y * _cos;
  z = tmp.z;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  _cos = cos(- rot->getY());
  _sin = sin(- rot->getY());
  x = tmp.x * _cos - tmp.z * _sin;
  y = tmp.y;
  z = tmp.x * _sin + tmp.z * _cos;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  _cos = cos(rot->getX());
  _sin = sin(rot->getX());
  x = tmp.x;
  y = tmp.y * _cos - tmp.z * _sin;
  z = tmp.y * _sin + tmp.z * _cos;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;
  
  *n = tmp;
}

void		Spot::applyRotation2(t_pt *n, AObject *rot)
{
  t_pt		tmp = *n;
  double	_cos = 0;
  double	_sin = 0;
  double	x;
  double	y;
  double	z;

  _cos = cos(- rot->getX());
  _sin = sin(- rot->getX());
  x = tmp.x;
  y = tmp.y * _cos - tmp.z * _sin;
  z = tmp.y * _sin + tmp.z * _cos;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  _cos = cos(rot->getY());
  _sin = sin(rot->getY());
  x = tmp.x * _cos - tmp.z * _sin;
  y = tmp.y;
  z = tmp.x * _sin + tmp.z * _cos;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  _cos = cos(rot->getZ());
  _sin = sin(rot->getZ());
  x = tmp.x * _cos - tmp.y * _sin;
  y = tmp.x * _sin + tmp.y * _cos;
  z = tmp.z;
  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  *n = tmp;
}

void		Spot::colorSeparator(unsigned int *blue, unsigned int *green,
				     unsigned int *red, unsigned int a)
{
  *blue = a & 0x0000FF;
  a = a >> 8;
  *green = a & 0x0000FF;
  a = a >> 8;
  *red = a & 0x0000FF;

}

unsigned int	Spot::colorUnificator(unsigned int red, unsigned int green, unsigned int blue)
{
  int	c;

  c = 0;
  c = c >> 16;
  c = red;
  c = c << 8;
  c += green;
  c = c << 8;
  c += blue;
  return (c);
}

unsigned int	Spot::mergeColors2(unsigned int color1, unsigned int color2, double coef)
{
  unsigned int	r1 = 0;
  unsigned int	g1 = 0;
  unsigned int	b1 = 0;
  unsigned int	r2 = 0;
  unsigned int	g2 = 0;
  unsigned int	b2 = 0;

  colorSeparator(&b1, &g1, &r1, color1);
  colorSeparator(&b2, &g2, &r2, color2);

  r1 = r1 * coef + r2 * (1 - coef);
  if (r1 > 255)
    r1 = 255;
  g1 = g1 * coef + g2 * (1 - coef);
  if (g1 > 255)
    g1 = 255;
  b1 = b1 * coef + b2 * (1 - coef);
  if (b1 > 255)
    b1 = 255;

  return colorUnificator(r1, g1, b1);
}

unsigned int	Spot::postProcess(drt::render::Scene * scene, Camera * camera, Ray * ray,
				  AObject * obj, double k, unsigned int color)
{
  t_pt		p;
  t_pt		l;
  t_pt		n;
  double	cosa;
  std::map<unsigned int, drt::render::Scene::t_Item *> objects = scene->getObjects();
  drt::render::Scene::t_Item	*lastFound = nullptr;
  drt::render::Scene::t_Item	*light = nullptr;
  unsigned int	tmpcolor;
  AObject *objTrans = nullptr;
  AObject *objRot = nullptr;

  for (auto b = objects.cbegin(); b != objects.cend(); b++)
    {
      Spot *tmp = dynamic_cast<Spot *> ((*b).second->object);
      if (tmp)
	{
	  if (tmp == this)
	    color = 0x000000;
	  break;
	}
    }
  for (auto i = objects.cbegin(); i != objects.cend(); i++)
    {
      if ((*i).second->object == obj)
	lastFound = (*i).second;
      if ((*i).second->object == this)
	light = (*i).second;
    }
  tmpcolor = lastFound->object->getColor();
  camera->reset();
  ray->reset();
  // t_pt tmpCam;
  // tmpCam.x = camera->getX();
  // tmpCam.y = camera->getY();
  // tmpCam.z = camera->getZ();
  int d = 0;
  for (auto a = lastFound->subItems.cbegin(); a != lastFound->subItems.cend(); a++)
    {
      if (d == 0)
	objTrans = (*a)->object;
      if (d == 1)
	objRot = (*a)->object;
      (*a)->object->preProcess(camera, ray);
      d++;
    }
  AObject *spotTrans = (*light->subItems.cbegin())->object;

  t_pt tmpCam;
  tmpCam.x = camera->getX();
  tmpCam.y = camera->getY();
  tmpCam.z = camera->getZ();

  x = spotTrans->getX();
  y = spotTrans->getY();
  z = spotTrans->getZ();
  p.x = camera->getX() + ray->getX() * k;
  p.y = camera->getY() + ray->getY() * k;
  p.z = camera->getZ() + ray->getZ() * k;
  tmpCam.x -= objTrans->getX();
  tmpCam.y -= objTrans->getY();
  tmpCam.z -= objTrans->getZ();
  n = obj->getNormale(p, tmpCam);

  // applyRotation(&n, objRot);
  l.x = x - objTrans->getX();
  l.y = y - objTrans->getY();
  l.z = z - objTrans->getZ();
  applyRotation2(&l, objRot);
  l.x -= p.x;
  l.y -= p.y;
  l.z -= p.z;

  this->normalize(&n);
  this->normalize(&l);
  cosa = (n.x * l.x) + (n.y * l.y) + (n.z * l.z);
  if (cosa < 0)
    cosa = 0;
  tmpcolor = applyLight(cosa, tmpcolor);
  tmpcolor = mergeColors2(tmpcolor, color, 0.5);
  return tmpcolor;
}
