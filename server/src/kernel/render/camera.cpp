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
