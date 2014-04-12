#include "Reflection.hpp"

Reflection::Reflection(double c) {
  coef = c;
}

Reflection::Reflection(Reflection &r) {
  coef = r.getCoef();
}

double	Reflection::getCoef() {
  return coef;
}
