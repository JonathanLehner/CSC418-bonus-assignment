#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // printf("intersect triangle \n");
  ////////////////////////////////////////////////////////////////////////////
  //how to calculate: intersection point lies on plane and inside triangle
  //then solve for t    
  Eigen::Vector3d onplane = std::get<0>(corners);
  Eigen::Vector3d inplane1 = std::get<1>(corners) - onplane;
  Eigen::Vector3d inplane2 = std::get<2>(corners) - onplane;
  Eigen::Vector3d normal = inplane1.cross(inplane2).normalized();
  double projection = (ray.direction).dot(normal);

  // printf("projection p %f %f %f %f \n", ray.direction[0], ray.direction[1], ray.direction[2], projection);
  if(abs(projection) < 0.0000001){ //parallel to plane
    return false;
  }
  else{
    Eigen::Vector3d origin_to_plane = onplane - ray.origin;
    t = origin_to_plane.dot(normal)/projection;
    if(t < min_t){
      return false;
    }
    Eigen::Vector3d intersection_point = ray.origin + ray.direction * t;
    //find out if area of the three triangles is the same, exactly then is the point inside the triangle
    double area_triangle = inplane1.cross(inplane2).norm();//*0.5 we multiply by 2 to erase 0.5
    Eigen::Vector3d ip_to0 = onplane - intersection_point;
    Eigen::Vector3d ip_to1 = std::get<1>(corners) - intersection_point;
    Eigen::Vector3d ip_to2 = std::get<2>(corners) - intersection_point;
    double triag0 = ip_to0.cross(ip_to1).norm();
    double triag1 = ip_to1.cross(ip_to2).norm();
    double triag2 = ip_to2.cross(ip_to0).norm();
    n = normal; //normal of triangle is normal of plane

    if(abs(triag0 + triag1 + triag2 - area_triangle) < 0.00000000001){
      return true;
    }
    else{
      return false;
    }

    return true;
  }
}


