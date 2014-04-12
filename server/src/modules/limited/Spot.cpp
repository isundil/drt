#include <cmath>
#include <iostream>
#include "Spot.hpp"
#include "Scene.hpp"

unsigned int	Spot::transparency(t_pt p, Ray *r, drt::render::Scene::t_Item *obj,
				   unsigned int color, drt::render::Scene *scene,
				   std::map<unsigned int, drt::render::Scene::t_Item *> objects)
{
  Camera	cam(p.x, p.y, p.z);
  Ray		ray(*r);
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
  return tmpcolor;
}

unsigned int	Spot::postProcess(drt::render::Scene * scene, Camera * camera, Ray * ray,
				  AObject * obj, double k, unsigned int color)
{
  t_pt		p2;
  std::map<unsigned int, drt::render::Scene::t_Item *> objects = scene->getObjects();
  drt::render::Scene::t_Item	*lastFound = nullptr;
  unsigned int	tmpcolor;

  for (auto i = objects.cbegin(); i != objects.cend(); i++)
      if ((*i).second->object == obj)
		lastFound = (*i).second;

  tmpcolor = lastFound->object->getColor();

  camera->reset();
  ray->reset();
  p2.x = camera->getX() + ray->getX() * k;
  p2.y = camera->getY() + ray->getY() * k;
  p2.z = camera->getZ() + ray->getZ() * k;
  tmpcolor = transparency(p2, ray, lastFound, tmpcolor, scene, objects);

  return tmpcolor;
}
