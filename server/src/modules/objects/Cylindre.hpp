#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cylindre : public AMathObject {
public:

  Cylindre(double r);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
