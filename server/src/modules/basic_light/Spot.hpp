#pragma once

#include "AObject.hpp"
#include "Scene.hpp"

#define SQ(a) (a * a)

class	Camera;
class	Ray;
class	Scene;

class		Spot : public AObject {
public:

  Spot();
  Spot(Spot &);

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int);
  virtual unsigned int	getColor() {return 0;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return x;}
  virtual double	getY() {return y;}
  virtual double	getZ() {return z;}
  virtual AObject	*clone() {return new Spot(*this);}
  unsigned int		applyLight(double, unsigned int);
  void			normalize(t_pt *);
  void			applyRotation(t_pt *n, AObject *rot);
  void			applyRotation2(t_pt *n, AObject *rot);

private:
  double	x;
  double	y;
  double	z;
};
