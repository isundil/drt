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

  // x = (double)camera->getX();
  y = (double)camera->getY() * (double)cosx - (double)camera->getZ() * (double)sinx;
  z = (double)camera->getY() * (double)sinx + (double)camera->getZ() * (double)cosx;
  // camera->setX((double)((double)x - (double)camera->getX()));
  camera->setY((double)((double)y - (double)camera->getY()));
  camera->setZ((double)((double)z - (double)camera->getZ()));

  // x = (double)ray->getX();
  y = (double)ray->getY() * (double)cosx - (double)ray->getZ() * (double)sinx;
  z = (double)ray->getY() * (double)sinx + (double)ray->getZ() * (double)cosx;
  // ray->setX((double)((double)x - (double)ray->getX()));
  ray->setY((double)((double)y - (double)ray->getY()));
  ray->setZ((double)((double)z - (double)ray->getZ()));
}

void	Rotation::yRotation(Camera * camera, Ray * ray)
{
  // rotation en y
  double	roty = (double)(- this->_y);// + camera->getRY();
  double	cosy = cos(roty);
  double	siny = sin(roty);
  double	x;
  double	y;
  double	z;

  x = (double)camera->getX() * (double)cosy - (double)camera->getZ() * (double)siny;
  // y = (double)camera->getY();
  z = (double)camera->getX() * (double)siny + (double)camera->getZ() * (double)cosy;
  camera->setX((double)((double)x - (double)camera->getX()));
  // camera->setY((double)((double)y - (double)camera->getY()));
  camera->setZ((double)((double)z - (double)camera->getZ()));

  x = (double)ray->getX() * (double)cosy - (double)ray->getZ() * (double)siny;
  // y = (double)ray->getY();
  z = (double)ray->getX() * (double)siny + (double)ray->getZ() * (double)cosy;
  ray->setX((double)((double)x - (double)ray->getX()));
  // ray->setY((double)((double)y - (double)ray->getY()));
  ray->setZ((double)((double)z - (double)ray->getZ()));

  // double	roty = ((this->_y - camera->getRY()) * M_PI) / 180;
  // double	cosy = cos(roty);
  // double	siny = sin(roty);
  // double	x = camera->getX() * cosy - camera->getZ() * siny;
  // double	y = camera->getY();
  // double	z = camera->getY() * cosy - camera->getZ() * siny;
  // camera->setX(x - camera->getX());
  // camera->setY(y - camera->getY());
  // camera->setZ(z - camera->getZ());
  // x = ray->getX() * cosy - ray->getZ() * siny;
  // y = ray->getY();
  // z = ray->getY() * cosy - ray->getZ() * siny;
  // ray->setX(x - ray->getX());
  // ray->setY(y - ray->getY());
  // ray->setZ(z - ray->getZ());
}

void	Rotation::zRotation(Camera * camera, Ray * ray)
{
  // rotation en z
  double	rotz = (double)(- this->_z);// + camera->getRZ();
  double	cosz = cos(rotz);
  double	sinz = sin(rotz);
  double	x;
  double	y;
  double	z;

  x = (double)camera->getX() * (double)cosz - (double)camera->getY() * (double)sinz;
  y = (double)camera->getX() * (double)sinz + (double)camera->getY() * (double)cosz;
  // z = (double)camera->getZ();
  camera->setX((double)((double)x - (double)camera->getX()));
  camera->setY((double)((double)y - (double)camera->getY()));
  // camera->setZ((double)((double)z - (double)camera->getZ()));

  x = (double)ray->getX() * (double)cosz - (double)ray->getY() * (double)sinz;
  y = (double)ray->getX() * (double)sinz + (double)ray->getY() * (double)cosz;
  // z = (double)ray->getZ();
  ray->setX((double)((double)x - (double)ray->getX()));
  ray->setY((double)((double)y - (double)ray->getY()));
  // ray->setZ((double)((double)z - (double)ray->getZ()));

  // double	rotz = ((this->_z - camera->getRZ()) * M_PI) / 180;
  // double	cosz = cos(rotz);
  // double	sinz = sin(rotz);
  // double	x = camera->getX() * cosz - camera->getZ() * sinz;
  // double	y = camera->getY() * cosz - camera->getZ() * sinz;
  // double	z = camera->getY();
  // camera->setX(x - camera->getX());
  // camera->setY(y - camera->getY());
  // camera->setZ(z - camera->getZ());
  // x = ray->getX() * cosz - camera->getZ() * sinz;
  // y = ray->getY() * cosz - camera->getZ() * sinz;
  // z = ray->getY();
  // ray->setX(x - ray->getX());
  // ray->setY(y - ray->getY());
  // ray->setZ(z - ray->getZ());
}

void	Rotation::preProcess(Camera * camera, Ray * ray)
{
  xRotation(camera, ray);
  // yRotation(camera, ray);
  // zRotation(camera, ray);
}

double	Rotation::computeEquation(Camera * camera, Ray * ray)
{
  return 0;
}

unsigned int	Rotation::getColor()
{
  return 0;
}
