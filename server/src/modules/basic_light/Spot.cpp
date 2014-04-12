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

  x = spotTrans->getX();
  y = spotTrans->getY();
  z = spotTrans->getZ();
  p.x = camera->getX() + ray->getX() * k;
  p.y = camera->getY() + ray->getY() * k;
  p.z = camera->getZ() + ray->getZ() * k;

  applyRotation(&p, objRot);
  n = obj->getNormale(p, l);
  p.x = p.x + objTrans->getX();
  p.y = p.y + objTrans->getY();
  p.z = p.z + objTrans->getZ();
  l.x = x - p.x;
  l.y = y - p.y;
  l.z = z - p.z;

  this->normalize(&n);
  this->normalize(&l);
  cosa = (n.x * l.x) + (n.y * l.y) + (n.z * l.z);
  if (cosa < 0)
    cosa = 0;
  tmpcolor = applyLight(cosa, tmpcolor);
  return tmpcolor;
}
