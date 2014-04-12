#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Plan : public AMathObject {
public:

  Plan(unsigned int color);
  Plan(Plan &);

  virtual double computeEquation(Camera * camera, Ray * ray);
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int _color) {return _color;}
  virtual unsigned int	getColor(){return color;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

  virtual double	getX() {return 0;}
  virtual double	getY() {return 0;}
  virtual double	getZ() {return 0;}
  virtual AObject	*clone() {return new Plan(*this);}

private:
  unsigned int	color;
};
