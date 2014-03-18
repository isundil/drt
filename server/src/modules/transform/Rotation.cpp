#include "Rotation.hpp"
#include "camera.hpp"
#include "ray.hpp"

Rotation::Rotation(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
}

void	Rotation::preProcess(Camera * camera, Ray * ray)
{
  // this is a transaltion
  double	x = camera->getX() - _x;
  double	y = camera->getY() - _y;
  double	z = camera->getZ() - _z;

  camera->setX(x);
  camera->setY(y);
  camera->setZ(z);
}

double	Rotation::computeEquation(Camera * camera, Ray * ray)
{
  return 0;
}

unsigned int	Rotation::getColor()
{
  return 0;
}
