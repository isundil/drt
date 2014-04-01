#pragma once
#include "AObject.hpp"

class Camera;
class Ray;

class		Translation : public AObject {
public:
  Translation(double x, double y, double z);
  virtual void		preProcess(Camera * camera, Ray * ray);
  virtual double        computeEquation(Camera * camera, Ray * ray);
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int) {return 0;}
  virtual unsigned int  getColor();
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

private:
  double	_x;
  double	_y;
  double	_z;
};

