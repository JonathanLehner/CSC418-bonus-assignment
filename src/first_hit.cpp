#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  size_t size = objects.size();
  t = -1;
  for(std::size_t i = 0; i < size; i++) {
    double current_t;
    Eigen::Vector3d current_n;
    //ray didn't intersect with the object
    //printf("no intersection with object %d \n", (int)i);
    if((*(objects[i])).intersect(ray, min_t, current_t, current_n) == false){
      //do nothing
    } 
    //ray intersected with the object 
    else{
      //printf("checking object %d %d \n", (int)i, (int)min_t);
      //printf("intersect \n");
      if(t == -1 || current_t < t){
        t = current_t;
        n = current_n;
        hit_id = (int)i;
      }
    }
  }
  if(t == -1){
    //printf("no intersection found \n");
    return false; //there were no intersections
  }
  else{
    //printf("intersection with %d \n", hit_id);
    return true;
  }
}

