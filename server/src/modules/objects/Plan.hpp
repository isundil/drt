#pragma once
#include <iostream>
#include "AMathObject.hpp"
#include "UtilSdeg.hpp"

class Plan : public AMathObject {
public:

  Plan(char color[3]);

  virtual double computeEquation(Camera * camera, Ray * ray);
};
