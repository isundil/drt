#pragma once

#include "AObject.hpp"

class Ray : public AObject {
public:
  
  Ray(double, double, double);
  virtual double	computeEquation(Camera * camera, Ray * ray) {
    (void)camera;
    (void)ray;
    return -1;
  }
  virtual unsigned int	getColor() {return 0;}
  double	getX() {return x;}
  double	getY() {return y;}
  double	getZ() {return z;}

private:
  double	x;
  double	y;
  double	z;
};
