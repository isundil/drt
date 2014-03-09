#include "Scene.hpp"

#include "Sphere.hpp"
#include "ray.hpp"
#include "camera.hpp"

int main(int ac, char **av) {

  // Scene	*scene = new Scene();
  Sphere *s = new Sphere();
  Camera *c = new Camera();
  Ray *r = new Ray();
  Scene	*scene = new Scene(c, r, s);

  scene->aff();
  scene->addObject(new Sphere());
  scene->aff();

  s->computeEquation(c, r);

  delete s;
  delete c;
  delete r;
  return 0;
}
