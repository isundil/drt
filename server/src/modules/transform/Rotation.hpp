#pragma once
#include "AObject.hpp"

class Camera;
class Ray;

class		Rotation : public AObject {
public:
  Rotation(double x, double y, double z);
  virtual void		preProcess(Camera * camera, Ray * ray);
  virtual double        computeEquation(Camera * camera, Ray * ray);
  virtual void		postProcess() {}
  virtual unsigned int  getColor();

private:
  double	_x;
  double	_y;
  double	_z;

  void			xRotation(Camera * camera, Ray * ray);
  void			yRotation(Camera * camera, Ray * ray);
  void			zRotation(Camera * camera, Ray * ray);
};

