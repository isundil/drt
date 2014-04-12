#pragma once

#include "AObject.hpp"

class	Camera;
class	Ray;
class	Scene;

class		Transparency : public AObject {
public:

  Transparency(double c);
  Transparency(Transparency &);

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int color) {return color;}
  virtual unsigned int	getColor() {return 0;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return 0;}
  virtual double	getY() {return 0;}
  virtual double	getZ() {return 0;}
  virtual AObject	*clone() {return new Transparency(*this);}
  double		getCoef();

private:
  double		coef;
};
