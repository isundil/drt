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
  double	rotx = ((this->_x - camera->getX()) * M_PI) / 180;
  double	cosx = cos(rotx);
  double	sinx = sin(rotx);
  double	x = camera->getX();
  double	y = camera->getY() * cosx - camera->getZ() * sinx;
  double	z = camera->getY() * cosx - camera->getZ() * sinx;
  camera->setX(x);
  camera->setY(y);
  camera->setZ(z);
  x = ray->getX();
  y = ray->getY() * cosx - ray->getZ() * sinx;
  z = ray->getY() * cosx - ray->getZ() * sinx;
  ray->setX(x);
  ray->setY(y);
  ray->setZ(z);
}

void	Rotation::yRotation(Camera * camera, Ray * ray)
{
  // rotation en y
  double	roty = ((this->_y - camera->getY()) * M_PI) / 180;
  double	cosy = cos(roty);
  double	siny = sin(roty);
  double	x = camera->getX() * cosy - camera->getZ() * siny;
  double	y = camera->getY();
  double	z = camera->getY() * cosy - camera->getZ() * siny;
  camera->setX(x - camera->getX());
  camera->setY(y - camera->getY());
  camera->setZ(z - camera->getZ());
  x = ray->getX() * cosy - ray->getZ() * siny;
  y = ray->getY();
  z = ray->getY() * cosy - ray->getZ() * siny;
  ray->setX(x - ray->getX());
  ray->setY(y - ray->getY());
  ray->setZ(z - ray->getZ());
}

void	Rotation::zRotation(Camera * camera, Ray * ray)
{
  // rotation en z
  double	rotz = ((this->_z - camera->getZ()) * M_PI) / 180;
  double	cosz = cos(rotz);
  double	sinz = sin(rotz);
  double	x = camera->getX() * cosz - camera->getZ() * sinz;
  double	y = camera->getY() * cosz - camera->getZ() * sinz;
  double	z = camera->getY();
  camera->setX(x);
  camera->setY(y);
  camera->setZ(z);
  x = ray->getX() * cosz - camera->getZ() * sinz;
  y = ray->getY() * cosz - camera->getZ() * sinz;
  z = ray->getY();
  ray->setX(x);
  ray->setY(y);
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
