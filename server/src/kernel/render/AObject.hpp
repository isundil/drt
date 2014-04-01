#pragma once

class	Ray;
class	Camera;
namespace drt {
  namespace render {
    class Scene;
  }
}

typedef struct	s_pt {
  double	x;
  double	y;
  double	z;
}		t_pt;

class AObject {
public:

  virtual ~AObject() {};
  virtual double	computeEquation(Camera * camera, Ray * ray) = 0;
  virtual void		preProcess(Camera * camera, Ray * ray) = 0;
  virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int) = 0;
  virtual unsigned int	getColor() = 0;
  virtual t_pt		getNormale(t_pt, t_pt) = 0;
};


  // virtual unsigned int	postProcess(drt::render::Scene *, Camera *, Ray *, AObject *, double, unsigned int) {return 0;}
  // virtual t_pt		getNormale(t_pt, t_pt) {t_pt t; return t;}

