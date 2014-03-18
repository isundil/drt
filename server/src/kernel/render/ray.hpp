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
  virtual void		undoPreProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
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

  
};

