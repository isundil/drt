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

  double	getX() {return x + mod_x;}
  double	getY() {return y + mod_y;}
  double	getZ() {return z + mod_z;}
  double	getRX() {return rx;}
  double	getRY() {return ry;}
  double	getRZ() {return rz;}

  void		setX(double _x) {mod_x = _x;}
  void		setY(double _y) {mod_y = _y;}
  void		setZ(double _z) {mod_z = _z;}

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
