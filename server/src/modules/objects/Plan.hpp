#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Plan : public AMathObject {
public:

  Plan();

  virtual double computeEquation(Camera * camera, Ray * ray);
};
