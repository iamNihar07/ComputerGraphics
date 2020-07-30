// Gupte, Nihar.
// nag6441
// 2020-04-25
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"

//----------------------------------------------------------
#define INSIDE (0)
#define LEFT   (1)
#define RIGHT  (2)
#define BELOW  (4)
#define ABOVE  (8)

#define EPSILON (1e-13)

int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax );

//----------------------------------------------------------
int clipLine( Line *l, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the clipLine algorithm here.
  //       Arguments:
  //           l : a pointer to the line to clip.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               clip against.
  //
  //       Compute the codes of the two endpoints of the line l
  //         using _regionCode().
  //
  //       In an infinite while loop,
  //         Do a trivial accept if possible.
  //         Do a trivial reject if possible.
  //         If neither is possible, select one of the point
  //           codes that's not in the INSIDE region.
  //         If it's ABOVE, slide the point to the yMax line.
  //         ElIf it's BELOW, slide the point to the yMin line.
  //         ElIf it's RIGHT, slide the point to the xMax line.
  //         Elif it's LEFT, slide the point to the xMin line.
  //         Else an error occurred.  Print a message and exit.
  //         Update whichever point got slid in l.
  //         Recompute the code of that point.
  //
  // This routine should return 1 if trivial accept happens, 0 if
  // trivial reject happens.
  //
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   You can look at the code in the Clipping handout as a
  //   reference, but remember that code is written in Python and
  //   this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT

  int p1Out = 0, p2Out = 0, anOutCode = 0; //from handout
  double p1x = l->p1X;
  double p1y = l->p1Y;
  double p2x = l->p2X;
  double p2y = l->p2Y;

  double x=0,y=0; //temp variables for calculating the new l coordinates

  while(1) //infinite loop
  {
    p1Out = _regionCode(p1x,p1y,xMin,yMin,xMax,yMax);
    p2Out = _regionCode(p2x,p2y,xMin,yMin,xMax,yMax);

    if(p1Out == INSIDE && p2Out == INSIDE) //trivial accept
    {
      return 1;
    }
    if((p1Out & p2Out) != INSIDE) //trivial reject if bitwise AND is not zero, so both points are outside
    {
      return 0;
    }

    //selecting a point that is outside
    if(p1Out == INSIDE) 
    {
      anOutCode = p2Out; //selecting p2 as outside since p1 is inside
    }
    else
    {
      anOutCode = p1Out; //selecting p1 as outside since p2 is inside
    }

    if(anOutCode & ABOVE) //move point along the line down to yMax
    {
      x = p1x + (p2x - p1x)*(yMax-p1y)/(p2y-p1y);
      y = yMax;
    }
    else if(anOutCode & BELOW) //move point along the line up to yMin
    {
      x = p1x + (p2x - p1x)*(yMin-p1y)/(p2y-p1y);
      y = yMin;
    }
    else if(anOutCode & RIGHT) //move point along the line over to xMax
    {
      x = xMax;
      y = p1y + (p2y - p1y)*(xMax-p1x)/(p2x-p1x);
    }
    else if(anOutCode & LEFT) //move point along the line over to xMin
    {
      x = xMin;
      y = p1y + (p2y - p1y)*(xMin-p1x)/(p2x-p1x);
    }
    else
    {
      fprintf(stderr,"ERROR: point does not belong to any region.\n");
      exit(1);
    }
    
    //updating the new coordinates for l for recomputation
    if(anOutCode == p1Out) //update new coordinates for p1Out using above algorithm since p1 was outside
    {
      p1x = x;
      p1y = y;
      //modifying the lines
      l->p1X = x;
      l->p1Y = y;
    }
    else //update new cordinates for p2Out using above algorithm since p2 was outside
    {
      p2x = x;
      p2y = y;
      //modifying the lines
      l->p2X = x;
      l->p2Y = y;
    }   
  }

}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  // TODO: Print an 'l' line for the given Line l.
  printf("l %8.1f %8.1f %8.1f %8.1f\n", l->p1X, l->p1Y, l->p2X, l->p2Y);
}

//----------------------------------------------------------
int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the region code computation here.
  //       Arguments:
  //           x, y
  //             : the point whose region must be computed.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               check against.
  //
  //       Assume the region is INSIDE to start.
  //       Check against xMin to see if the point is LEFT.
  //       Check against xMax to see if the point is RIGHT.
  //       Check against yMin to see if the point is BELOW.
  //       Check against yMax to see if the point is ABOVE.
  //
  // This routine should return the code with the proper bits set.
  // (The bits are already defined above for your use.)

  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   (1) Ensure that you do EPSILON comparisions when
  //       checking against xMin, yMin, xMax, yMax.  EPSILON is
  //       already defined above for your use.
  //   (2) You can look at the code in the Clipping handout as a
  //       reference, but remember that code is written in Python
  //       and this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT

  int val = INSIDE; //assuming region is INSIDE to start

  //from handout
  if((xMin-x) > EPSILON)
  {
    val = val | LEFT;
  }
  else if((x-xMax) > EPSILON)
  {
    val = val | RIGHT;
  }

  if((yMin-y) > EPSILON)
  {
    val = val | BELOW;
  }
  else if((y-yMax) > EPSILON)
  {
    val = val | ABOVE;
  }

  return val;
}

//----------------------------------------------------------
