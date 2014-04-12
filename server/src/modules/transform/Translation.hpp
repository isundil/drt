#pragma once
#include "AObject.hpp"

class Camera;
class Ray;

class		Translation : public AObject {
public:
  Translation(double x, double y, double z);
  Translation(Translation &);

  virtual void		preProcess(Camera * camera, Ray * ray);
  virtual double        computeEquation(Camera * camera, Ray * ray);
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int _color) {return _color;}
  virtual unsigned int  getColor();
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

  virtual double	getX() {return _x;}
  virtual double	getY() {return _y;}
  virtual double	getZ() {return _z;}
  virtual AObject	*clone() {return new Translation(*this);}

private:
  double	_x;
  double	_y;
  double	_z;
};

