#include "Sphere.h"
#include "Ray.h"
#include <Eigen/Dense>
#include <math.h>       /* sqrt */

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //cases: does not intersect, tangent/hit
  //we consider the plane with ray.origin, ray.direction and the sphere center  
  // printf("ray direction %f %f %f \n", ray.direction[0], ray.direction[1], ray.direction[2]);
  Eigen::Vector3d to_center = center - ray.origin;
  // printf("to center %f %f %f \n", to_center[0], to_center[1], to_center[2]);
  Eigen::Vector3d projection = ray.direction.normalized() * to_center.dot(ray.direction.normalized());
  // printf("projection %f %f %f \n", projection[0], projection[1], projection[2]);
  Eigen::Vector3d orthogonal = to_center - projection;
  // printf("orthogonal %f %f %f \n", orthogonal[0], orthogonal[1], orthogonal[2]);

  // printf("intersect sphere %f \n", orthogonal.norm());
  if(orthogonal.norm() > radius){//ray misses the sphere
    return false;
  }
  else{
    double x1 = sqrt(radius*radius - orthogonal.norm()*orthogonal.norm());
    double x2 = -x1;
    Eigen::Vector3d intersection_point = ray.origin + projection - x1*(projection.normalized());
    n = (intersection_point - center).normalized();
    t = (intersection_point - ray.origin).norm()/ray.direction.norm();
    // printf("intersect sphere %f %f %f %f \n", center[0], center[1], center[2], t);
    // printf("normal %f %f %f \n", n[0], n[1], n[2]);
    if(t > min_t){
      return true;
    }
    else{
      return false;
    }

  }
}

