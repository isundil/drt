#pragma once

#include "IObject.hh"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Cylindre.hpp"
#include "plan.hpp"

#include "AModule.hpp"

#define SPHERE		1
#define CYLINDRE	2
#define CONE		3
#define PLAN		4

typedef	struct		s_rayon {
  char			color[3];
  int			r;
}			t_rayon;

typedef	struct		s_angle {
  char			color[3];
  double		a;
}			t_angle;

class		basicShape : public AModule {
public:
  basicShape();
  AObject	*getInstance(unsigned short subModule, char *data);
};
