#pragma once

#include <utility>
#include <math.h>
#include <utility>

class UtilSdeg {
public:
  static std::pair<double, double> getRoots(double a, double b, double c);
  static double	getK(std::pair<double, double>, double);
};
