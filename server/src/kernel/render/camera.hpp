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

};
