#pragma once
#include "AObject.hpp"

// translation -> coordonees camera - coordonees objet lors du calcul.
// 
// solution 1:
// -> retourner une camera modifiee
// 
// solution 2:
// -> modifier camera avant calcul puis remettre valeurs d'origines apres calcul
// 
// probleme :
// dans les deux cas me faut acceder a la camera.

class Camera;
class Ray;

class		Translation : public AObject {
public:
  Translation(double x, double y, double z);
  virtual void		preProcess(Camera * camera, Ray * ray);
  virtual double        computeEquation(Camera * camera, Ray * ray);
  virtual void		postProcess() {}
  virtual unsigned int  getColor();

private:
  double	_x;
  double	_y;
  double	_z;
};

