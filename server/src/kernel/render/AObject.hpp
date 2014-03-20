#pragma once

class	Ray;
class	Camera;

class AObject {
public:

  virtual ~AObject() {};
  virtual double	computeEquation(Camera * camera, Ray * ray) = 0;
  virtual void		preProcess(Camera * camera, Ray * ray) = 0;
  virtual void		postProcess() = 0;
  virtual unsigned int	getColor() = 0;
  // virtual Ray *		getNormale() = 0; // will be used for light
};
