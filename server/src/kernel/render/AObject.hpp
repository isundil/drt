#pragma once

class	Ray;
class	Camera;

class AObject {
public:

  // should have a function for pre process
  // virtual void	preProcess(Camera * camera, Ray * ray) = 0;
  virtual double	computeEquation(Camera * camera, Ray * ray) = 0;
  // should have a function for post process
  // virtual void	postProcess() = 0;
  virtual unsigned int	getColor() = 0;

};
