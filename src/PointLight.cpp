#include "PointLight.h"

void PointLight::direction(
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
  // position of light
  // std::numeric_limits<double>::infinity()
  Eigen::Vector3d light_point = PointLight::p;
  d = light_point - q;
  max_t = d.norm();
  d = d.normalized();
}
