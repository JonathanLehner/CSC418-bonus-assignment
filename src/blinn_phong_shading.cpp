#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  // Given a ray and its hit in the scene, return the Blinn-Phong shading
  // contribution over all _visible_ light sources (e.g., take into account
  // shadows). 
  // 
  // Inputs:
  //   ray  incoming ray
  //   hit_id  index into objects of the object just hit by ray
  //   t  _parametric_ distance along ray to hit
  //   n  unit surface normal at hit
  //   objects  list of objects in the scene
  //   lights  list of lights in the scene
  // Returns shaded color collected by this ray as rgb 3-vector
  Eigen::Vector3d rgb;
  Eigen::Vector3d ambient = (*(*objects[hit_id]).material).ka;
  Eigen::Vector3d diffuse = (*(*objects[hit_id]).material).kd;
  Eigen::Vector3d specular = (*(*objects[hit_id]).material).ks;
  double phong_exponent = (*(*objects[hit_id]).material).phong_exponent;
    
  rgb = ambient;
  Eigen::Vector3d intersection_point = ray.origin + ray.direction * t;

  size_t size = lights.size();
  for(std::size_t i = 0; i < size; i++) {
    //diffuse shading
    Eigen::Vector3d light_direction;
    double max_t;
    (*lights[i]).direction(intersection_point, light_direction, max_t); //max_t is parametric distance to light

    Eigen::Vector3d light_contrib = Eigen::Vector3d(0,0,0);
    //printf("%f ", max_t);
    Eigen::Vector3d intensity = (*lights[i]).I;
    double Ld = n.dot(light_direction);
    Ld = Ld > 0 ? Ld : 0;
    light_contrib += Ld * (diffuse.array() * intensity.array()).matrix();

    //specular shading
    Eigen::Vector3d to_eye = -ray.direction.normalized();
    Eigen::Vector3d h = (to_eye + light_direction).normalized(); //to the power of phone exponent
    double Ls = n.dot(h);
    Ls = Ls > 0 ? Ls : 0;
    Ls = pow(Ls, phong_exponent);
    light_contrib += Ls * (specular.array() * intensity.array()).matrix();

    //shadows -- shoot rays at each light source
    Ray shadow_ray = Ray();
    shadow_ray.origin = intersection_point; 
    shadow_ray.direction = light_direction; // direction to light
    int shadow_hit_id;
    double shadow_t;
    Eigen::Vector3d shadow_n;
    bool hit = first_hit(shadow_ray, 0.000001, objects, shadow_hit_id, shadow_t, shadow_n);
    if(hit){
      light_contrib = Eigen::Vector3d(0,0,0);
    }
    rgb += light_contrib;
  } 
  return rgb;

}
