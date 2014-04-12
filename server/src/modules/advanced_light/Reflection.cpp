#include "Reflection.hpp"
#include <iostream>

Reflection::Reflection(double c) {
  std::cout << "Reflection" << std::endl;
  coef = c;
}

Reflection::Reflection(Reflection &r) {
  std::cout << "Reflection" << std::endl;
  coef = r.getCoef();
}

double	Reflection::getCoef() {
  return coef;
}
