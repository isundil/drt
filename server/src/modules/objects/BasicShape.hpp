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

typedef	struct		s_rayon {
  unsigned int		color;
  int			r;
}			t_rayon;

typedef	struct		s_angle {
  unsigned int		color;
  double		a;
}			t_angle;

class		basicShape : public drt::module::AModule {
public:
  basicShape(void *dlHandler, const std::string &name, createFncPtr fnc);
  AObject	*getInstance(unsigned short subModule, char *data);
  const std::string	&getName() const;

private:
  basicShape();
};
