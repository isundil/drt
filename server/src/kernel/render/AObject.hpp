#pragma once

class	Ray;
class	Camera;

class AObject {
public:

  virtual double	computeEquation(Camera * camera, Ray * ray) = 0;
  virtual void		preProcess(Camera * camera, Ray * ray) = 0;
  virtual void		postProcess() = 0;
  virtual unsigned int	getColor() = 0;

};
