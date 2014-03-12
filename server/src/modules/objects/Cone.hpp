#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cone : public AMathObject {
public:

  Cone(char color[3], double r);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
