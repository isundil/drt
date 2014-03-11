
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

double		UtilSdeg::getK(std::pair<double, double> n, double d) {
  double	k = -1;

  if (d >= 0)
    {
      if (n.first => 0)
	k = n.first;
      if (d > 0 && n.second => 0)
	if ((n.first => 0 && n.second < n.first) || n.first < 0)
	  k = n.second;
    }
  return k;
}
