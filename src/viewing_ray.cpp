#include "viewing_ray.h"
#include <Eigen/Core>

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // When t=1, then ray.origin + t*ray.direction should land exactly on the center of the
  // pixel (i,j)
  // i pixel row index
  // j pixel column index
  //convert pixels to camera coordinate system... circle for instance is at (0,0,9)
  //have to convert to -0.888 to 0.888 and -0.5 to 0.5
  Eigen::Vector3d corg = camera.e;
  double l = -camera.width/2;
  double r = camera.width/2;
  double t = camera.height/2;
  double b = -camera.height/2;

  double us = l + camera.width * (j + 0.5) / (double)width; //convert to camera coordinates
  double vs = t - camera.height * (i + 0.5) / (double)height; //convert to camera coordinates
  double ws = -camera.d;
  Eigen::Vector3d s = us*camera.u + vs*camera.v + ws*camera.w;
  // if(s[0] < 0.25 && s[0] > -0.25 && s[1] < 0.25 && s[1] > -0.25)
  //   printf("data %d %d \n", j, i);
  //   printf("Vector %f %f %f \n", s[0], s[1], s[2]);
  Eigen::Vector3d origin = camera.e; //eye of camera

  //point must be in world coordinates with pixels 640*360
  //Eigen::Vector3d point = Eigen::Vector3d(i, j, -camera.w*camera.d);//camera.d = 1
  Eigen::Vector3d direction = s.normalized(); //point - origin; 
  ray.origin = origin;
  ray.direction = direction;
}

