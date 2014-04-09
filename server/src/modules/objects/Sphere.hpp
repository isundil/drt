#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Sphere : public AMathObject {
public:

  Sphere(unsigned int color, double r);

  virtual double	computeEquation(Camera * camera, Ray * ray);
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int _color) {std::cout << "Sphere postProcess" << std::endl; return _color;}
  virtual unsigned int	getColor(){return color;}
  virtual t_pt		getNormale(t_pt, t_pt);

  virtual double	getX() {return 0;}
  virtual double	getY() {return 0;}
  virtual double	getZ() {return 0;}

private:
  double	r;
  unsigned int	color;
};
