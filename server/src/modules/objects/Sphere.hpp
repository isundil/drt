#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Sphere : public AMathObject {
public:

  Sphere(unsigned int color, double r);

  virtual double	computeEquation(Camera * camera, Ray * ray);
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int) {return 0;}
  virtual unsigned int	getColor(){return color;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

private:
  double	r;
  unsigned int	color;
};
