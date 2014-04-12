#include "Reflection.hpp"
#include <iostream>

Reflection::Reflection(double c) {
  coef = c;
  std::cout << "Reflection : coef = " << coef << std::endl;
}

Reflection::Reflection(Reflection &r) {
  coef = r.getCoef();
  std::cout << "Reflection : coef = " << coef << std::endl;
}

double	Reflection::getCoef() {
  return coef;
}
