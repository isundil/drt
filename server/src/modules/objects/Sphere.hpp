#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Sphere : public AMathObject {
public:

  Sphere(unsigned int color, double r);

  virtual double	computeEquation(Camera * camera, Ray * ray);
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual void		postProcess() {};
  virtual void		undoPreProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual unsigned int	getColor(){return color;}

private:
  double	r;
  unsigned int	color;
};
