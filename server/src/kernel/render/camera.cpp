#include <string>
#include "camera.hpp"

Camera::Camera(short x, short y, short z, double rx, double ry, double rz) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
  this->rx = rx;
  this->ry = ry;
  this->rz = rz;
  mod_x = 0;
  mod_y = 0;
  mod_z = 0;
}

Camera::Camera(Camera &cam) {
  this->x = cam.getX();
  this->y = cam.getY();
  this->z = cam.getZ();
  this->rx = cam.getRX();
  this->ry = cam.getRY();
  this->rz = cam.getRZ();
}

void	Camera::reset()
{
  mod_x = 0;
  mod_y = 0;
  mod_z = 0;
}

double	Camera::getX()
{return (x + mod_x);}

double	Camera::getY()
{return (y + mod_y);}

double	Camera::getZ()
{return (z + mod_z);}

double	Camera::getRX()
{return rx;}

double	Camera::getRY()
{return ry;}

double	Camera::getRZ()
{return rz;}

void		Camera::setX(double _x)
{mod_x = _x;}

void		Camera::setY(double _y)
{mod_y = _y;}

void		Camera::setZ(double _z)
{mod_z = _z;}

