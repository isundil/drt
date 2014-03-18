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
  double	x = camera->getX() - _x;
  double	y = camera->getY() - _y;
  double	z = camera->getZ() - _z;

  camera->setX(x);
  camera->setY(y);
  camera->setZ(z);
  // probleme : comment je modifie la camera ? dois-je retourner une copie modifiee ?
}

double	Translation::computeEquation(Camera * camera, Ray * ray)
{
  return 0;
}

unsigned int	Translation::getColor()
{
  return 0;
}
