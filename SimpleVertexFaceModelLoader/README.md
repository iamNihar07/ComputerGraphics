# Simple Vertex Face Model Loader
Allocates Vertex and Face Models for a structure by loading formatted data from a .svfm file (Simple Vertex Face Model). The vertices and faces are then printed to create a viewable ".sdf" file.

## Execution Instructions <br>
>$ gcc -o hmwk_01 hmwk_01.c model.c vertex.c face.c <br>
>$ ./hmwk_01 pyramid.svfm <br>

You can replace pyramid.svfm by other .svfm files

## Format of SVFM Files
- Blank lines are ignored. (A blank line has no
      characters at all or is just whitespace.)

- Lines with '#' as the first non-whitespace character are
      comments and are ignored.

- Lines with 'v' as the first non-whitespace character are
      Vertex lines.  There will be three numbers following the
      'v': the X, Y, and Z coordinates of the vertex.  The 'v' and
      the coordinates will be separated by whitespace.  Example:

        v 27.34  16  8.9

- Lines with 'f' as the first non-whitespace character are
      Face lines.  There will be three integers following the
      'f': the numbers of the three vertices making up the face.
      (Faces are triangles.)  The 'f' and the vertex numbers will
      be separated by whitespace.  Example:

        f  17   23   56

      In the SVFM file, the vertices are numbered 1 to n.  In
      your program, the vertices will be refered to as 0 to n-1.
      

- If a line starts with any other non-whitespace character, it
      is silently ignored.  
      
      
  #### Submitted for homework 1 assignment, CSE 4303- Computer Graphics coursework at the University of Texas at Arlington. Read 'HMWK_01.txt' for more details
