#include "Sphere.hpp"
#include "ray.hpp"
#include "camera.hpp"

int main(int ac, char **av) {

  Sphere *s = new Sphere();
  Camera *c = new Camera();
  Ray *r = new Ray();

  s->computeEquation(c, r);

  delete s;
  delete c;
  delete r;
  return 0;
}
