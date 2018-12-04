#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Inputs:
  //   in  incoming _unit_ ray direction
  //   n  surface _unit_ normal about which to reflect
  // Returns outward _unit_ ray direction
   
  Eigen::Vector3d incoming = in; 
  Eigen::Vector3d normal = -n;
  Eigen::Vector3d out = in - 2 * in.dot(n) * n;
  return out;
  ////////////////////////////////////////////////////////////////////////////
}
