#include <cmath>
#include <iostream>
#include "Spot.hpp"
#include "Scene.hpp"

Spot::Spot() {
  std::cout << "Spot initialized" << std::endl;
  x = 0;
  y = 0;
  z = 0;
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
  Camera	saveCamera(*camera);

  for (auto i = objects.cbegin(); i != objects.cend(); i++)
    {
      if ((*i).second->object == obj)
	lastFound = (*i).second;
      if ((*i).second->object == this)
	light = (*i).second;
    }
  saveCamera.reset();
  ray->reset();
  for (auto a = lastFound->subItems.cbegin(); a != lastFound->subItems.cend(); a++)
    (*a)->object->preProcess(&saveCamera, ray);
  auto i = light->subItems.cbegin();
  x += (*i)->object->getX();
  y += (*i)->object->getY();
  z += (*i)->object->getZ();

  p.x = saveCamera.getX() + ray->getX() * k;
  p.y = saveCamera.getY() + ray->getY() * k;
  p.z = saveCamera.getZ() + ray->getZ() * k;
  auto a = lastFound->subItems.cbegin();
  l.x = x - (p.x + (*a)->object->getX());
  l.y = y - (p.y + (*a)->object->getY());
  l.z = z - (p.z + (*a)->object->getZ());

  n = obj->getNormale(p, l);

  this->normalize(&n);
  this->normalize(&l);
  cosa = (n.x * l.x) + (n.y * l.y) + (n.z * l.z);
  if (cosa < 0)
    cosa = 0;
  color = applyLight(cosa, color);
  return color;
}
