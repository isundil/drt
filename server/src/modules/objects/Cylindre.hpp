#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cylindre : public AMathObject {
public:

  Cylindre(char color[3], double r);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
