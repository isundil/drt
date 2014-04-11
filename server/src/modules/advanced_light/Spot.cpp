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

  colorSeparator(&b, &g, &r, color);

  r = cosa * r;
  if (r > 255)
    r = 255;
  g = cosa * g;
  if (g > 255)
    g = 255;
  b = cosa * b;
  if (b > 255)
    b = 255;

  color = colorUnificator(r, g, b);
  return color;
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

unsigned int	Spot::mergeColors(unsigned int color1, unsigned int color2)
{
  unsigned int	r1 = 0;
  unsigned int	g1 = 0;
  unsigned int	b1 = 0;
  unsigned int	r2 = 0;
  unsigned int	g2 = 0;
  unsigned int	b2 = 0;

  colorSeparator(&b1, &g1, &r1, color1);
  colorSeparator(&b2, &g2, &r2, color2);

  // r1 = r1 * coef + r2 * (1 - coef);
  // if (r1 > 255)
  //   r1 = 255;
  // g1 = g1 * coef + g2 * (1 - coef);
  // if (g1 > 255)
  //   g1 = 255;
  // b1 = b1 * coef + b2 * (1 - coef);
  // if (b1 > 255)
  //   b1 = 255;

  r1 = r1 + r2;
  if (r1 > 255)
    r1 = 255;
  g1 = g1 + g2;
  if (g1 > 255)
    g1 = 255;
  b1 = b1 + b2;
  if (b1 > 255)
    b1 = 255;

  return colorUnificator(r1, g1, b1);
}

bool		Spot::isInShadow(std::map<unsigned int, drt::render::Scene::t_Item *> objects, t_pt p,
				 t_pt l, drt::render::Scene::t_Item *obj)
{
  p.x += (*obj->subItems.cbegin())->object->getX();
  p.y += (*obj->subItems.cbegin())->object->getY();
  p.z += (*obj->subItems.cbegin())->object->getZ();
  Camera	camera(p.x, p.y, p.z);
  Ray		ray(l.x, l.y, l.z);
  double	k = -1;
  bool		res = false;

  for (auto i = objects.cbegin(); i != objects.cend(); i++)
    {
      camera.reset();
      ray.reset();
      if ((*i).second->object != obj->object)
      	{
      	  for (auto a = (*i).second->subItems.cbegin(); a != (*i).second->subItems.cend(); a++)
	    (*a)->object->preProcess(&camera, &ray);
      	  k = (*i).second->object->computeEquation(&camera, &ray);
      	  if (k < 1 && k > 0)
	    res = true;
	}
    }
  // return false;
  return res;
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
  unsigned int	nbSpots = 0;
  bool		shadow = false;

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
  for (auto a = lastFound->subItems.cbegin(); a != lastFound->subItems.cend(); a++)
    (*a)->object->preProcess(camera, ray);
  drt::render::Scene::t_Item *i = (*light->subItems.cbegin());
  drt::render::Scene::t_Item *a = (*lastFound->subItems.cbegin());
  x = i->object->getX();
  y = i->object->getY();
  z = i->object->getZ();
  p.x = camera->getX() + ray->getX() * k;
  p.y = camera->getY() + ray->getY() * k;
  p.z = camera->getZ() + ray->getZ() * k;
  l.x = x - p.x - a->object->getX();
  l.y = y - p.y - a->object->getY();
  l.z = z - p.z - a->object->getZ();

  shadow = isInShadow(objects, p, l, lastFound);
  n = obj->getNormale(p, l);
  this->normalize(&n);
  this->normalize(&l);
  cosa = (n.x * l.x) + (n.y * l.y) + (n.z * l.z);
  if (cosa < 0)
    cosa = 0;
  if (shadow == false)
    tmpcolor = applyLight(cosa, tmpcolor);
  else
    tmpcolor = 0;
  // for (auto b = objects.cbegin(); b != objects.cend(); b++)
  //   {
  //     Spot *tmp = dynamic_cast<Spot *> ((*b).second->object);
  //     if (tmp)
  // 	nbSpots++;
  //   }
  color = mergeColors(tmpcolor, color);
  return color;
}
