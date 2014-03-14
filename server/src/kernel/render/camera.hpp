#pragma once

#include "AObject.hpp"

class Camera : public AObject {
public:

  Camera(short, short, short, double, double, double);
  virtual double	computeEquation(Camera * camera, Ray * ray) {
    (void)camera;
    (void)ray;
    return -1;
  }
  virtual unsigned int	getColor() {return 0;}

  double	getX() {return x;}
  double	getY() {return y;}
  double	getZ() {return z;}
  double	getRX() {return rx;}
  double	getRY() {return ry;}
  double	getRZ() {return rz;}

private:
  double	x;
  double	y;
  double	z;
  double	rx;
  double	ry;
  double	rz;

};
