#pragma once

#include "AObject.hpp"
#include "Scene.hpp"

#define SQ(a) (a * a)

class	Camera;
class	Ray;
class	Scene;

class		BasicSpot : public AObject {
public:

  BasicSpot();
  BasicSpot(BasicSpot &);

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int);
  virtual unsigned int	getColor() {return 0;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return x;}
  virtual double	getY() {return y;}
  virtual double	getZ() {return z;}
  virtual AObject	*clone() {return new BasicSpot(*this);}
  unsigned int		applyLight(double, unsigned int);
  void			normalize(t_pt *);
  void			applyRotation(t_pt *n, AObject *rot);
  void			applyRotation2(t_pt *n, AObject *rot);
  unsigned int		mergeColors2(unsigned int color1, unsigned int color2, double coef);
  void			colorSeparator(unsigned int *, unsigned int *, unsigned int *, unsigned int);
  unsigned int		colorUnificator(unsigned int red, unsigned int green, unsigned int blue);

private:
  double	x;
  double	y;
  double	z;
};
