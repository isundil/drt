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

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int);
  virtual unsigned int	getColor() {return color;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return x;}
  virtual double	getY() {return y;}
  virtual double	getZ() {return z;}
  void			colorSeparator(unsigned int *, unsigned int *, unsigned int *, unsigned int);
  unsigned int		colorUnificator(unsigned int red, unsigned int green, unsigned int blue);
  unsigned int		mergeColors(unsigned int color1, unsigned int color2, unsigned int max);
  unsigned int		applyLight(double, unsigned int);
  bool			isInShadow(std::map<unsigned int, drt::render::Scene::t_Item *>, t_pt, t_pt, drt::render::Scene::t_Item *);
  void			normalize(t_pt *);
  void			applyRotation(t_pt *n, AObject *rot);

private:
  double	x;
  double	y;
  double	z;
  unsigned int	color;
};