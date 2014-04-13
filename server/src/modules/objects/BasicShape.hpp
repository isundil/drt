#pragma once

#include "IObject.hh"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Cylindre.hpp"
#include "Plan.hpp"

#include "AModule.hpp"

#define SPHERE		1
#define CYLINDRE	2
#define CONE		3
#define PLAN		4

typedef	struct		__attribute__ ((packed)) s_rayon {
  unsigned int		color;
  short			r;
  short			lxa;
  short			lxi;
  short			lya;
  short			lyi;
  short			lza;
  short			lzi;
}			t_rayon;

typedef	struct		__attribute__ ((packed)) s_angle {
  unsigned int		color;
  double		a;
  short			lxa;
  short			lxi;
  short			lya;
  short			lyi;
  short			lza;
  short			lzi;
}			t_angle;

typedef	struct		__attribute__ ((packed)) s_plan {
  unsigned int		color;
  short			lxa;
  short			lxi;
  short			lya;
  short			lyi;
  short			lza;
  short			lzi;
}			t_plan;

class		basicShape {
public:
  basicShape();

};
