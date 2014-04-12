#pragma once
#include "AObject.hpp"

#include "camera.hpp"
#include "ray.hpp"

#define SQ(a) (a * a)

typedef struct		s_lim {
  double		limXMax;
  double		limXMin;
  double		limYMax;
  double		limYMin;
  double		limZMax;
  double		limZMin;
}			t_lim;

class AMathObject : public AObject {
public:
  AMathObject() : AObject() {};

  virtual double computeEquation(Camera * camera, Ray * ray) = 0;
};

