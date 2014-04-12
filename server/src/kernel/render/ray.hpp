#pragma once

#include "AObject.hpp"

class Ray : public AObject {
public:
  
  Ray(double, double, double);
  Ray(Ray &r);
  virtual double	computeEquation(Camera * camera, Ray * ray) {
    (void)camera;
    (void)ray;
    return -1;
  }
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int) {return 0;}
  virtual unsigned int	getColor() {return 0;}
  virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

  virtual double	getX();
  virtual double	getY();
  virtual double	getZ();

  virtual AObject	*clone() {return new Ray(*this);}

  double	getModX();
  double	getModY();
  double	getModZ();

  void		setX(double _x);
  void		setY(double _y);
  void		setZ(double _z);

  void		reset();

private:
  double	x;
  double	y;
  double	z;

  double	mod_x;
  double	mod_y;
  double	mod_z;
};

