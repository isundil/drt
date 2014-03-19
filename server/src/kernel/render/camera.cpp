#include <string>
#include "camera.hpp"

Camera::Camera(short x, short y, short z, double rx, double ry, double rz) : AObject() {
  this->x = (double)x;
  this->y = (double)y;
  this->z = (double)z;
  this->rx = (double)rx;
  this->ry = (double)ry;
  this->rz = (double)rz;
  mod_x = (double)0;
  mod_y = (double)0;
  mod_z = (double)0;
}

Camera::Camera(Camera &cam) {
  this->x = (double)cam.getX();
  this->y = (double)cam.getY();
  this->z = (double)cam.getZ();
  this->rx = (double)cam.getRX();
  this->ry = (double)cam.getRY();
  this->rz = (double)cam.getRZ();
}

void	Camera::reset()
{
  mod_x = (double)0;
  mod_y = (double)0;
  mod_z = (double)0;
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

void		Camera::setX(double _x)
{mod_x = (double)_x;}

void		Camera::setY(double _y)
{mod_y = (double)_y;}

void		Camera::setZ(double _z)
{mod_z = (double)_z;}

