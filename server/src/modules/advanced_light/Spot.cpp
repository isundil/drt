#include <cmath>
#include <iostream>
#include "Spot.hpp"
#include "Scene.hpp"

Spot::Spot() {
  x = 0;
  y = 0;
  z = 0;
  color = 0xFFFFFF;
  refMax = 0;
  transMax = 0;
}

Spot::Spot(Spot &s) {
  x = 0;
  y = 0;
  z = 0;
  color = 0xFFFFFF;
  refMax = 0;
  transMax = 0;
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

unsigned int	Spot::mergeColors(unsigned int color1, unsigned int color2, unsigned int max)
{
  unsigned int	r1 = 0;
  unsigned int	g1 = 0;
  unsigned int	b1 = 0;
  unsigned int	r2 = 0;
  unsigned int	g2 = 0;
  unsigned int	b2 = 0;
  unsigned int	rm = 0;
  unsigned int	gm = 0;
  unsigned int	bm = 0;

  colorSeparator(&b1, &g1, &r1, color1);
  colorSeparator(&b2, &g2, &r2, color2);
  colorSeparator(&bm, &gm, &rm, max);

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
  if (r1 > rm)
    r1 = rm;
  g1 = g1 + g2;
  if (g1 > gm)
    g1 = gm;
  b1 = b1 + b2;
  if (b1 > bm)
    b1 = bm;

  return colorUnificator(r1, g1, b1);
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
  return res;
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

unsigned int	Spot::transparency(t_pt p, Ray *r, t_pt norm, drt::render::Scene::t_Item *obj,
				   unsigned int color, drt::render::Scene *scene,
				   std::map<unsigned int, drt::render::Scene::t_Item *> objects)
{
  Camera	cam(p.x, p.y, p.z);
  Ray		ray(*r);
  double	k = -1;
  double	tmpk = k;
  unsigned int	tmpcolor = 0;
  drt::render::Scene::t_Item	*lastFound = nullptr;

  transMax++;
  // std::cout << "transMax = " << transMax << std::endl;

  for (auto i = objects.cbegin(); i != objects.cend(); i++)
    {
      cam.reset();
      ray.reset();
      if ((*i).second->object != obj->object)
      	{
	  // (*i).second->object->preProcess(); // I don't think the object will need a preProcess func.
	  for (auto a = (*i).second->subItems.cbegin(); a != (*i).second->subItems.cend(); a++)
	    (*a)->object->preProcess(&cam, &ray);
	  tmpk = (*i).second->object->computeEquation(&cam, &ray);
	  if ((tmpk < k || k == -1) && tmpk >= 0)
	    {
	      k = tmpk;
	      tmpcolor = (*i).second->object->getColor();
	      lastFound = (*i).second;
	    }
	}
    }
  if (lastFound != nullptr)
    for (auto it = objects.cbegin(); it != objects.cend(); it++)
      tmpcolor = (*it).second->object->postProcess(scene, &cam, &ray, lastFound->object, k, tmpcolor);
  transMax--;
  // std::cout << "found color [" << tmpcolor << "] to merge with [" << color << "]" << std::endl;
  return mergeColors2(tmpcolor, color, 0.2); // recuperer le coef de l'objet
}

unsigned int	Spot::reflection(t_pt p, Ray *r, t_pt norm, drt::render::Scene::t_Item *obj,
				   unsigned int color, drt::render::Scene *scene,
				   std::map<unsigned int, drt::render::Scene::t_Item *> objects)
{
  Camera	cam(p.x, p.y, p.z);
  t_pt		tmpr;
  double	p_s;
  tmpr.x = r->getX();
  tmpr.y = r->getY();
  tmpr.z = r->getZ();
  this->normalize(&norm);
  this->normalize(&tmpr);
  p_s = norm.x * tmpr.x + norm.y * tmpr.y + norm.z * tmpr.z;
  tmpr.x = (-2.f * norm.x) * p_s + tmpr.x;
  tmpr.y = (-2.f * norm.y) * p_s + tmpr.y;
  tmpr.z = (-2.f * norm.z) * p_s + tmpr.z;
  Ray		ray(tmpr.x, tmpr.y, tmpr.z);
  double	k = -1;
  double	tmpk = k;
  unsigned int	tmpcolor = 0;
  drt::render::Scene::t_Item	*lastFound = nullptr;

  for (auto i = objects.cbegin(); i != objects.cend(); i++)
    {
      cam.reset();
      ray.reset();
      if ((*i).second->object != obj->object)
      	{
	  // (*i).second->object->preProcess(); // I don't think the object will need a preProcess func.
	  for (auto a = (*i).second->subItems.cbegin(); a != (*i).second->subItems.cend(); a++)
	    (*a)->object->preProcess(&cam, &ray);
	  tmpk = (*i).second->object->computeEquation(&cam, &ray);
	  if ((tmpk < k || k == -1) && tmpk >= 0)
	    {
	      k = tmpk;
	      tmpcolor = (*i).second->object->getColor();
	      lastFound = (*i).second;
	    }
	}
    }
  if (lastFound != nullptr)
    for (auto it = objects.cbegin(); it != objects.cend(); it++)
      tmpcolor = (*it).second->object->postProcess(scene, &cam, &ray, lastFound->object, k, tmpcolor);
  return mergeColors2(tmpcolor, color, 0.5); // recuperer le coef de l'objet
}

unsigned int	Spot::postProcess(drt::render::Scene * scene, Camera * camera, Ray * ray,
				  AObject * obj, double k, unsigned int color)
{
  t_pt		p;
  t_pt		p2;
  t_pt		l;
  t_pt		n;
  double	cosa;
  std::map<unsigned int, drt::render::Scene::t_Item *> objects = scene->getObjects();
  drt::render::Scene::t_Item	*lastFound = nullptr;
  drt::render::Scene::t_Item	*light = nullptr;
  unsigned int	tmpcolor;
  unsigned int	transColor = 0;
  unsigned int	reflectedColort = 0;
  unsigned int	nbSpots = 0;
  bool		shadow = false;
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
  p2 = p;

  applyRotation(&p, objRot);
  n = obj->getNormale(p, l);

  if (obj->getColor() == 0xFF4682B4)		// a modifier plus tard pour mettre des valeur setables
    {
      camera->reset();
      ray->reset();
      p2.x = camera->getX() + ray->getX() * k;
      p2.y = camera->getY() + ray->getY() * k;
      p2.z = camera->getZ() + ray->getZ() * k;
      tmpcolor = transparency(p2, ray, n, lastFound, tmpcolor, scene, objects);
    }
  if (obj->getColor() == 0xFFFF0000)		// a modifier plus tard pour mettre des valeur setables
    {
      camera->reset();
      ray->reset();
      p2.x = camera->getX() + ray->getX() * k;
      p2.y = camera->getY() + ray->getY() * k;
      p2.z = camera->getZ() + ray->getZ() * k;
      tmpcolor = reflection(p2, ray, n, lastFound, tmpcolor, scene, objects);
    }

  // p.x = camera->getX() + ray->getX() * k;
  // p.y = camera->getY() + ray->getY() * k;
  // p.z = camera->getZ() + ray->getZ() * k;
  l.x = x - p.x - objTrans->getX();
  l.y = y - p.y - objTrans->getY();
  l.z = z - p.z - objTrans->getZ();

  shadow = isInShadow(objects, p, l, lastFound);

  this->normalize(&n);
  this->normalize(&l);
  cosa = (n.x * l.x) + (n.y * l.y) + (n.z * l.z);
  if (cosa < 0)
    cosa = 0;
  if (shadow == false)
    tmpcolor = applyLight(cosa, tmpcolor);
  else
    tmpcolor = 0;
  color = mergeColors(tmpcolor, color, 0xFFFFFF);
  return color;
}
