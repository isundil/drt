#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cylindre : public AMathObject {
public:

  Cylindre(unsigned int color, double r);

  virtual double computeEquation(Camera * camera, Ray * ray);
  virtual unsigned int	getColor(){return color;}

private:
  double	r;
  unsigned int	color;
};
