#include "Transparency.hpp"
#include <iostream>

Transparency::Transparency(double c) {
  coef = c;
  std::cout << "Transparency : coef = " << coef << std::endl;
}

Transparency::Transparency(Transparency &t) {
  coef = t.getCoef();
  std::cout << "Transparency : coef = " << coef << std::endl;
}

double	Transparency::getCoef() {
  return coef;
}
