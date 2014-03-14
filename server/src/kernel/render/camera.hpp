#pragma once

#include "AObject.hpp"

class Camera : public AObject {
public:

  Camera(short, short, short, double, double, double);
  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}

private:
  // short		x;
  // short		y;
  // short		z;
  // double	rx;
  // double	ry;
  // double	rz;
};
