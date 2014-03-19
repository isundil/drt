#include "Translation.hpp"
#include "camera.hpp"
#include "ray.hpp"

Translation::Translation(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
}

void	Translation::preProcess(Camera * camera, Ray * ray)
{
  camera->setX((double)-_x);
  camera->setY((double)-_y);
  camera->setZ((double)-_z);
  (void)ray;
}

double	Translation::computeEquation(Camera * camera, Ray * ray)
{
  return 0;
}

unsigned int	Translation::getColor()
{
  return 0;
}
