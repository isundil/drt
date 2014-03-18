#pragma once

#include "AObject.hpp"

class Ray : public AObject {
public:
  
  Ray(double, double, double);
  virtual double	computeEquation(Camera * camera, Ray * ray) {
    (void)camera;
    (void)ray;
    return -1;
  }
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual void		postProcess() {};
  virtual unsigned int	getColor() {return 0;}

  double	getX() const;
  double	getY() const;
  double	getZ() const;

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

