#include "Transparency.hpp"
#include <iostream>

Transparency::Transparency(double c) {
  coef = c;
}

Transparency::Transparency(Transparency &t) {
  coef = t.getCoef();
}

double	Transparency::getCoef() {
  return coef;
}
