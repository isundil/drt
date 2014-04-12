#include "Reflection.hpp"
#include <iostream>

Reflection::Reflection(double c) {
  coef = c;
}

Reflection::Reflection(Reflection &r) {
  coef = r.getCoef();
}

double	Reflection::getCoef() {
  return coef;
}
