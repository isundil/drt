#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Cone : public AMathObject {
public:

  Cone();

  virtual double computeEquation(Camera * camera, Ray * ray);
};
