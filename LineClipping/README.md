# Line Clipping using Cohen-Sutherland algorithm
Read lines (from a ".line" file) and clip them using the Cohen-Sutherland algorithm and the supplied view parameters (from a ".view" file).  The clipped lines are then printed (along with the canvas size) to create a viewable ".sdf" file.

## Execution Instructions <br>
>$ gcc -o hmwk_03 hmwk_03.c line.c view.c <br>
>$ ./hmwk_03 Tests/pyramid_01.line Tests/pyramid_01.view <br>

You can replace pyramid.svfm by other .svfm files and pyramid_01.view by other .view files

## Format of .line file
- Blank lines are ignored.  (A blank line has no
      characters at all or is just whitespace.)

- Lines with '#' as the first non-whitespace character are
      comments and are ignored.

- A line with an 'l' as the first non-whitespace character is
      a line line.  There will be four numbers following
      the 'l': the p1X, p1Y, p2X, p2Y coordinates of the two
      endpoints that define the line.  The 'l' and the coordinates
      will be separated by whitespace.  Example:

        l  237.4    123   8      96.1

      The coodinates may be either integer or floating
      point numbers.

- If a line starts with any other non-whitespace character, it
      is silently ignored.
      
## Format of .view file
 - Blank lines are ignored.  (A blank line has no
      characters at all or is just whitespace.)

- Lines with '#' as the first non-whitespace character are
      comments and are ignored.

- A line with a 'w' as the first non-whitespace character is
      the Worldspace line.  There will be four numbers following
      the 'w': the xMin, yMin, xMax, and yMax limits of the
      desired worldspace.  The 'w' and the limits will be
      separated by whitespace.  Example:

        w  1.1 2.2  16.5   23.3

- A line with a 'c' as the first non-whitespace character is
      the Canvas size line.  There will be two integers following
      the 'c': the width and the height of the canvas.  The 'c'
      and the width and height will be separated by whitespace.
      Example:

        c   500  400

- A line with an 's' as the first non-whitespace character is
      the usable Screenspace line.  There will be four numbers
      following the 's': the xMin, yMin, xMax, and yMax limits of
      the desired viewport.  The 's' and the limits will be
      separated by whitespace.  Example:

        s   0.10    0.15  0.80   0.75

- A line with a 'd' as the first non-whitespace character is
      the viewpoint Distance line.  There will be a number
      following the 'd': the position of the viewpoint on the z
      axis.  The 'd' and the viewpoint position will be separated
      by whitespace.  Example:

        d  12.9

      If the d is zero (or omitted entirely), the view represents
      a PARALLEL projection.  (If the d is non-zero, the view
      represents a PERSPECTIVE projection, with the viewpoint
      located at [ 0, 0, d ]T.)

- If a line starts with any other non-whitespace character, it
     is silently ignored.

#### Submitted for homework 3 assignment, CSE 4303 - Computer Graphics coursework at the University of Texas at Arlington. Read 'HMWK_03.txt' for more details
