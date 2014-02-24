
#include "UtilSdeg.hpp"

std::pair<double, double> UtilSdeg::getRoots(double a, double b, double c) {
  double disc = b * b - 4 * a * c;
  double n1 = -1, n2 = -1;

  if (disc >= 0) {
    n1 = (-b - sqrt(disc)) / (2 * a);
    if (disc > 0) {
      n2 = (-b + sqrt(disc)) / (2 * a);
    }
  }

  return { n1, n2 };
}
