#include <string>
#include "camera.hpp"

Camera::Camera(short x, short y, short z, double rx, double ry, double rz) : AObject() {
  this->x = x;
  this->y = y;
  this->z = z;
  this->rx = rx;
  this->ry = ry;
  this->rz = rz;
}

Camera::Camera(Camera &cam) {
  this->x = cam->getX();
  this->y = cam->getY();
  this->z = cam->getZ();
  this->rx = cam->getRX();
  this->ry = cam->getRY();
  this->rz = cam->getRZ();
}

void	Camera::reset()
{
  mod_x = 0;
  mod_y = 0;
  mod_z = 0;
}
