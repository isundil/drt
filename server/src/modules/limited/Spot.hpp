#pragma once

#include "AObject.hpp"
#include "Scene.hpp"
#include "AdvancedLight.hpp"

#define SQ(a) (a * a)

class	Camera;
class	Ray;
class	Scene;

class		Spot : public AObject {
public:

  Spot(t_param *params);
  Spot(Spot &);

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int);
  virtual unsigned int	getColor() {return color;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return x;}
  virtual double	getY() {return y;}
  virtual double	getZ() {return z;}
  virtual AObject	*clone() {return (AObject *) new Spot(*this);}
  void			colorSeparator(unsigned int *, unsigned int *, unsigned int *, unsigned int);
  unsigned int		transparency(t_pt, Ray *, drt::render::Scene::t_Item *, unsigned int, drt::render::Scene *, std::map<unsigned int, drt::render::Scene::t_Item *>);

private:
  double	x;
  double	y;
  double	z;
  unsigned int	color;
};
