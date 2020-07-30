// Gupte, Nihar.
// nag6441
// 2020-05-06

//----------------------------------------------------------
#include <stdio.h>

#include "visible.h"

//----------------------------------------------------------
int isVisible( Vertex *cameraPosition, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Purpose:  Determine if the triangle represented by
  //          vertices v1, v2, and v3 is visible from the given
  //          camera position.
  //
  //        Compute the toTriangle vector from the camera position
  //          to v1 of the triangle.
  //
  //        Derive the surface normal for the triangle by
  //          computing the cross product of the vector from v1
  //          to v2 with the vector from v1 to v3.
  //
  //        Compute the angle between the toTriangle vector and
  //          the surface normal vector.
  //
  //        Return 1 if this angle indicates the triangle is
  //          visible from the camera position, 0 otherwise.

  Vertex toTriangle, vectorA, vectorB, surface_normal;

  //getting toTriangle vector
  toTriangle.x = v1->x - cameraPosition->x;
  toTriangle.y = v1->y - cameraPosition->y;
  toTriangle.z = v1->z - cameraPosition->z;

  //vector a which is from v1 to v2
  vectorA.x = v2->x - v1->x;
  vectorA.y = v2->y - v1->y;
  vectorA.z = v2->z - v1->z;

  //vector b which is from v1 to v3
  vectorB.x = v3->x - v1->x;
  vectorB.y = v3->y - v1->y;
  vectorB.z = v3->z - v1->z;

  //getting normal to the surface by crossing vectors a and b
  surface_normal.x = (vectorA.y*vectorB.z)-(vectorA.z*vectorB.y);
  surface_normal.y = (vectorA.z*vectorB.x)-(vectorA.x*vectorB.z);
  surface_normal.z = (vectorA.x*vectorB.y)-(vectorA.y*vectorB.x);

  //calculating dot product between surface normal and toTriangle vector
  double dot_pdt = (toTriangle.x*surface_normal.x) + (toTriangle.y*surface_normal.y) + (toTriangle.z*surface_normal.z);

  if(dot_pdt<0) //dit product is negative between pi/2 and 3pi/2, so return 1
  {
    return 1;
  }
  else
  {
    return 0;
  }
  
}

//----------------------------------------------------------
