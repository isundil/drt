#pragma once

#include "AObject.hpp"

class Camera : public AObject {
public:

  Camera(short, short, short, double, double, double);
  Camera(Camera &);
  virtual double	computeEquation(Camera * camera, Ray * ray) {
    (void)camera;
    (void)ray;
    return -1;
  }
  virtual void		preProcess(Camera * camera, Ray * ray) {(void)camera; (void)ray;};
  virtual void		postProcess() {};
  virtual unsigned int	getColor() {return 0;}

  double	getX();
  double	getY();
  double	getZ();
  double	getRX();
  double	getRY();
  double	getRZ();

  void		setX(double _x);
  void		setY(double _y);
  void		setZ(double _z);

  void		reset();

private:
  double	x;
  double	y;
  double	z;
  double	rx;
  double	ry;
  double	rz;

  double	mod_x;
  double	mod_y;
  double	mod_z;

};
