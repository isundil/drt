#include "Rotation.hpp"
#include "camera.hpp"
#include "ray.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

Rotation::Rotation(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
}

void	Rotation::xRotation(Camera * camera, Ray * ray)
{
  // rotation en x
  double	rotx = (double)(- this->_x);// + camera->getRX();
  double	cosx = cos(rotx);
  double	sinx = sin(rotx);
  double	x;
  double	y;
  double	z;

  x = camera->getModX();
  y = camera->getY() * cosx - camera->getZ() * sinx;
  z = camera->getY() * sinx + camera->getZ() * cosx;
  camera->reset();
  camera->setX(x);
  camera->setY(y - camera->getY());
  camera->setZ(z - camera->getZ());

  x = ray->getModX();
  y = ray->getY() * cosx - ray->getZ() * sinx;
  z = ray->getY() * sinx + ray->getZ() * cosx;
  ray->reset();
  ray->setX(x);
  ray->setY(y - ray->getY());
  ray->setZ(z - ray->getZ());
}

void	Rotation::yRotation(Camera * camera, Ray * ray)
{
  // rotation en y
  double	roty = (double)(this->_y);// + camera->getRY();
  double	cosy = cos(roty);
  double	siny = sin(roty);
  double	x;
  double	y;
  double	z;

  x = camera->getX() * cosy - camera->getZ() * siny;
  y = camera->getModY();
  z = camera->getX() * siny + camera->getZ() * cosy;
  camera->reset();
  camera->setX(x - camera->getX());
  camera->setY(y);
  camera->setZ(z - camera->getZ());

  x = ray->getX() * cosy - ray->getZ() * siny;
  y = ray->getModY();
  z = ray->getX() * siny + ray->getZ() * cosy;
  ray->reset();
  ray->setX(x - ray->getX());
  ray->setY(y);
  ray->setZ(z - ray->getZ());
}

void	Rotation::zRotation(Camera * camera, Ray * ray)
{
  // rotation en z
  double	rotz = (double)(this->_z);// + camera->getRZ();
  double	cosz = cos(rotz);
  double	sinz = sin(rotz);
  double	x;
  double	y;
  double	z;

  x = camera->getX() * cosz - camera->getY() * sinz;
  y = camera->getX() * sinz + camera->getY() * cosz;
  z = camera->getModZ();
  camera->reset();
  camera->setX(x - camera->getX());
  camera->setY(y - camera->getY());
  camera->setZ(z);

  x = ray->getX() * cosz - ray->getY() * sinz;
  y = ray->getX() * sinz + ray->getY() * cosz;
  z = ray->getModZ();
  ray->reset();
  ray->setX(x - ray->getX());
  ray->setY(y - ray->getY());
  ray->setZ(z);
}

void	Rotation::preProcess(Camera * camera, Ray * ray)
{
  xRotation(camera, ray);
  yRotation(camera, ray);
  zRotation(camera, ray);
}

double	Rotation::computeEquation(Camera * camera, Ray * ray)
{
  return 0;
}

unsigned int	Rotation::getColor()
{
  return 0;
}
