// Gupte, Nihar.
// nag6441
// 2020-04-19
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "projection.h"

//----------------------------------------------------------
Projection *allocProjection()
{
  // TODO: Allocate a Projection structure.
  //       Return a pointer to the Projection structure as the
  //         result of this function.
  // (You can use calloc() to allocate zeroed out memory.)

  Projection *proj = (Projection *) calloc(1,sizeof(Projection)); //1 block in memory is allocated to Model structure of size of the type Model
  if(proj==NULL) //error
  {
    perror("Error in allocation of Projection.\n");
    exit(1);
  }

  return proj;
}

//----------------------------------------------------------
Projection *computeProjection( View *v )
{
  // TODO: Allocate a Projection structure (allocProjection()).
  //       Compute fx, fy, gx, gy, sx, sy, ax, ay using the
  //         information in the given view.
  //       Save the view's camera distance in the projection.
  //       Return a pointer to the allocated projection structure
  //         as the value of this function.

  Projection *proj = allocProjection();

  proj->m_fx = -(v->m_worldXMin); //fx
  proj->m_fy = -(v->m_worldYMin); //fy

  proj->m_gx= v->m_width * v->m_viewportXMin; //gx
  proj->m_gy= v->m_height * v->m_viewportYMin; //gy

  proj->m_sx = v->m_width * (v->m_viewportXMax - v->m_viewportXMin) / ( v->m_worldXMax - v->m_worldXMin); //sx
  proj->m_sy = v->m_height * (v->m_viewportYMax - v->m_viewportYMin) / ( v->m_worldYMax - v->m_worldYMin); //sy

  proj->m_ax = (proj->m_fx * proj->m_sx) + proj->m_gx; //ax
  proj->m_ay = (proj->m_fy * proj->m_sy) + proj->m_gy; //ay

  proj->m_cameraDistance = v->m_cameraDistance; //save the view's camera distance in the projection

  return proj;
}

//----------------------------------------------------------
void dumpProjection( Projection *p )
{
  printf( "#- Projection parameters ---------------\n" );
  printf( "# (fx, fy) : ( %13.6f, %13.6f )\n", p->m_fx, p->m_fy );
  printf( "# (gx, gy) : ( %13.6f, %13.6f )\n", p->m_gx, p->m_gy );
  printf( "# (sx, sy) : ( %13.6f, %13.6f )\n", p->m_sx, p->m_sy );
  printf( "# (ax, ay) : ( %13.6f, %13.6f )\n", p->m_ax, p->m_ay );
  printf( "# Camera distance : %13.6f\n", p->m_cameraDistance );
  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeProjection( Projection *p )
{
  // TODO: Free the projection structure.
  if(p!=NULL)
  {
    free(p);
  }
}

//----------------------------------------------------------
void projectVertex( Projection *p, Vertex *v1, Vertex *v2 )
{
  // TODO: Using the projection parameters, project the
  //         coordinates of vertex v1 and save the results
  //         in vertex v2.
  //       If the camera distance is != 0, do the projection
  //         as PERSPECTIVE.  If the camera distance is == 0,
  //         do the projection as PARALLEL.
  //       Do NOT perspective project any vertex that has
  //         its z coordinate >= the camera distance.  (Print
  //         a warning message to stderr if this happens.)

  if(p->m_cameraDistance!=0) //perspective projection
  {
    if(v1->z>=p->m_cameraDistance)
    {
      fprintf(stderr,"Warning:vertex z coordinate >= camera distance.\n"); 
    }
    v2->x = (p->m_sx * v1->x/(1-(v1->z/p->m_cameraDistance))) + p->m_ax;
    v2->y = (p->m_sy * v1->y/(1-(v1->z/p->m_cameraDistance))) + p->m_ay;
    v2->z = 0;
  }
  else //parallel
  {
    v2->x = (v1->x * p->m_sx) + p->m_ax;
    v2->y = (v1->y * p->m_sy) + p->m_ay;
    v2->z=0;
  }
  
}

void projectVertexList( Projection *p, Vertex *v, int numVertices )
{
  // TODO: Use projectVertex() to project each of the
  //         numVertices starting at v onto itself.
  
  int i=0;
  for(i=0;i<numVertices;i++)
  {
    projectVertex(p,v,v); //projecting v onto itself
    v++; //next vertex for next iteration
  }
}

//----------------------------------------------------------

