#prama once

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

class		basicShape : public AModule {
public:
  basicShape();
  IObject	*getInstance(unsigned short subModule, char *data);
};
