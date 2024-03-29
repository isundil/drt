#pragma once

#include "AObject.hpp"
#include "Scene.hpp"

#define SQ(a) (a * a)

class	Camera;
class	Ray;
class	Scene;

typedef	struct		s_shadow {
  unsigned int		color;
  double		coef;
  bool			shadow;
}			t_shadow;

class		Spot : public AObject {
public:

  Spot(unsigned int);
  Spot(Spot &);

  virtual double	computeEquation(Camera * camera, Ray * ray) {return -1;}
  virtual void		preProcess(Camera * camera, Ray * ray) {}
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int);
  virtual unsigned int	getColor() {return color;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}
  virtual double	getX() {return x;}
  virtual double	getY() {return y;}
  virtual double	getZ() {return z;}
  virtual AObject	*clone() {return new Spot(*this);}
  void			colorSeparator(unsigned int *, unsigned int *, unsigned int *, unsigned int);
  unsigned int		colorUnificator(unsigned int red, unsigned int green, unsigned int blue);
  unsigned int		mergeColors(unsigned int color1, unsigned int color2, unsigned int max);
  unsigned int		applyLight(double, unsigned int, drt::render::Scene::t_Item *);
  bool			isInShadow(std::map<unsigned int, drt::render::Scene::t_Item *>, t_pt, t_pt, drt::render::Scene::t_Item *);
  void			normalize(t_pt *);
  void			applyRotation(t_pt *n, AObject *rot);
  void			applyRotation2(t_pt *n, AObject *rot);
  unsigned int		mergeColors2(unsigned int color1, unsigned int color2, double coef);
  unsigned int		mergeColors3(unsigned int color1, unsigned int color2);
  unsigned int		transparency(t_pt, Ray *, t_pt , drt::render::Scene::t_Item *, unsigned int, drt::render::Scene *, std::map<unsigned int, drt::render::Scene::t_Item *>);
  unsigned int		reflection(t_pt, Ray *, t_pt , drt::render::Scene::t_Item *, unsigned int, drt::render::Scene *, std::map<unsigned int, drt::render::Scene::t_Item *>);
  t_shadow       	getShadow(std::map<unsigned int, drt::render::Scene::t_Item *> objects, t_pt p, t_pt l, drt::render::Scene::t_Item *obj);
  unsigned int		applyShadow(double cosa, unsigned int color, drt::render::Scene::t_Item *obj, t_shadow shadow);

  void		describe();

private:
  double	x;
  double	y;
  double	z;
  unsigned int	color;

  unsigned int	refMax;
  unsigned int	transMax;
};
