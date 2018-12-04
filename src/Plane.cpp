#include "Plane.h"
#include "Ray.h"
#include <Eigen/Dense>
#include <math.h>       /* sqrt */

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //how to calculate: intersection point lies on plane and on ray from origin
  //then solve for t    
  double projection = (ray.direction).dot(normal);
  // printf("projection p %f %f %f %f \n", ray.direction[0], ray.direction[1], ray.direction[2], projection);
  if(abs(projection) < 0.0000001){ //parallel to plane
    return false;
  }
  else{

    Eigen::Vector3d origin_to_plane = point - ray.origin;
    // printf("point %f %f %f \n", point[0], point[1], point[2]);
    // printf("otop %f %f %f \n", origin_to_plane[0], origin_to_plane[1], origin_to_plane[2]);
    t = origin_to_plane.dot(normal)/projection;
    // if(t > 0) {
    //   printf("intersect plane \n");
    //   printf("%f %f \n", projection, t);
    // }
    if(t < min_t){
      return false;
    }
    // printf("normal %f %f %f \n", normal[0], normal[1], normal[2]);
    n = normal; //plane normal is the same at all points on the plane
    return true;
  }
}
