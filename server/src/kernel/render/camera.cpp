#include <string>
#include "camera.hpp"

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

