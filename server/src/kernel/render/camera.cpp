#include <string>
#include "camera.hpp"
#include "ray.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

Camera::Camera(short x, short y, short z, double rx, double ry, double rz) : AObject() {
  this->x = (double)x;
  this->y = (double)y;
  this->z = (double)z;
  this->rx = (double)rx;
  this->ry = (double)ry;
  this->rz = (double)rz;
  mod_x = (double)0.f;
  mod_y = (double)0.f;
  mod_z = (double)0.f;
}

Camera::Camera(double x, double y, double z) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
  this->rx = 0.f;
  this->ry = 0.f;
  this->rz = 0.f;
  mod_x = 0.f;
  mod_y = 0.f;
  mod_z = 0.f;
}

Camera::Camera(Camera &cam) {
  this->x = (double)cam.getX();
  this->y = (double)cam.getY();
  this->z = (double)cam.getZ();
  this->rx = (double)cam.getRX();
  this->ry = (double)cam.getRY();
  this->rz = (double)cam.getRZ();
  mod_x = (double)0.f;
  mod_y = (double)0.f;
  mod_z = (double)0.f;
}

Ray	*Camera::getRay(double _x, double _y, double _z)
{
  t_pt		p;
  double	x = 0;
  double	y = 0;
  double	z = 0;
  double	_cos;
  double	_sin;

  p.x = _x - this->x;
  p.y = _y - this->y;
  p.z = _z - this->z;

  _cos = cos(this->rx);
  _sin = sin(this->rx);
  x = p.x;
  y = p.y * _cos - p.z * _sin;
  z = p.y * _sin + p.z * _cos;
  p.x = x;
  p.y = y;
  p.z = z;

  _cos = cos(- this->ry);
  _sin = sin(- this->ry);
  x = p.x * _cos - p.z * _sin;
  y = p.y;
  z = p.x * _sin + p.z * _cos;
  p.x = x;
  p.y = y;
  p.z = z;

  _cos = cos(- this->rz);
  _sin = sin(- this->rz);
  x = p.x * _cos - p.y * _sin;
  y = p.x * _sin + p.y * _cos;
  z = p.z;
  p.x = x + this->x;
  p.y = y + this->y;
  p.z = z + this->z;

  return new Ray(p.x, p.y, p.z);
}

void	Camera::reset()
{
  mod_x = (double)0.f;
  mod_y = (double)0.f;
  mod_z = (double)0.f;
}

double	Camera::getX()
{return (double)((double)x + (double)mod_x);}

double	Camera::getY()
{return (double)((double)y + (double)mod_y);}

double	Camera::getZ()
{return (double)((double)z + (double)mod_z);}

double	Camera::getRX()
{return (double)rx;}

double	Camera::getRY()
{return (double)ry;}

double	Camera::getRZ()
{return (double)rz;}

double	Camera::getModX()
{return mod_x;}

double	Camera::getModY()
{return mod_y;}

double	Camera::getModZ()
{return mod_z;}

void		Camera::setX(double _x)
{mod_x = (double)_x;}

void		Camera::setY(double _y)
{mod_y = (double)_y;}

void		Camera::setZ(double _z)
{mod_z = (double)_z;}

