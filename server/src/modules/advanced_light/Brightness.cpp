#include "Brightness.hpp"
#include <iostream>

Brightness::Brightness(double c) {
  coef = c;
  std::cout << "Brightness coef = " << coef << std::endl;
}

Brightness::Brightness(Brightness &t) {
  coef = t.getCoef();
  std::cout << "Brightness coef = " << coef << std::endl;
}

double	Brightness::getCoef() {
  return coef;
}
