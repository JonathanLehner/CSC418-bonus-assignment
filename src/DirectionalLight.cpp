#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Given a query point return the direction _toward_ the Light.
  //
  // Input:
  //   q  3D query point in space
  // Outputs:
  //    d  3D direction from point toward light as a vector.
  //    max_t  parametric distance from q along d to light (may be inf)

  // d Direction _from_ light toward scene.
  Eigen::Vector3d light_direction = DirectionalLight::d;
  d = -light_direction.normalized();
  max_t = std::numeric_limits<double>::infinity();
}

