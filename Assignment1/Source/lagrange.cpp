#include <GL/glut.h>


#define DELTA_T 0.05
double B (int n, double t)
/* Evaluates the blending functions for Lagrange interpolation. */
{
   switch (n)
   {
      case 1 : return -t*(t-1.0)*(t-2.0)/6.0;
   	       break;
      case 2 : return (t+1.0)*(t-1.0)*(t-2.0)/2.0;
   	       break;
      case 3 : return -(t+1.0)*t*(t-2.0)/2.0;
   	       break;
      case 4 : return (t+1.0)*t*(t-1.0)/6.0;
   	       break;
   }
   return 0.0;// default case, should never happen
}

void Lagrange_interpolate (float px[],float py[],int number_of_points)
/* This procedure does Lagrange interpolation of the data. */
{
   int i;
   double t, x, y, b1, b2, b3, b4;

   glColor3f (1.0, 1.0, 1.0);  /* Draw curve in black. */
   glBegin (GL_LINE_STRIP);

      /* Handle first set of 4 points between t=-1 and t=0 separately. */
      for (t=-1.0; t<DELTA_T/2.0; t+=DELTA_T)
      {
         b1 = B(1,t);
         b2 = B(2,t);
         b3 = B(3,t);
         b4 = B(4,t);
         x = px[0]*b1 + px[1]*b2 + px[2]*b3 + px[3]*b4;
         y = py[0]*b1 + py[1]*b2 + py[2]*b3 + py[3]*b4;
         glVertex2d (x, y);
      }
   
      /*Handle middle segments. */
      for (i=1; i<=number_of_points-3; i++)
      {
         for (t=DELTA_T; t<1.0+DELTA_T/2.0; t+=DELTA_T)
         {
            b1 = B(1,t);
	        b2 = B(2,t);
	        b3 = B(3,t);
	        b4 = B(4,t);
	        x = px[i-1]*b1 + px[i]*b2 + px[i+1]*b3 + px[i+2]*b4;
	        y = py[i-1]*b1 + py[i]*b2 + py[i+1]*b3 + py[i+2]*b4;
	        glVertex2d (x, y);
         }
      }
   
      /* Handle the last set of 4 points between t=1.0 and t=2.0 separately. */
      for (t=1.0+DELTA_T; t<2.0+DELTA_T/2.0; t+=DELTA_T)
      {
         b1 = B(1,t);
         b2 = B(2,t);
         b3 = B(3,t);
         b4 = B(4,t);
         x = px[number_of_points-4]*b1 + px[number_of_points-3]*b2 +
             px[number_of_points-2]*b3 + px[number_of_points-1]*b4;
         y = py[number_of_points-4]*b1 + py[number_of_points-3]*b2 +
             py[number_of_points-2]*b3 + py[number_of_points-1]*b4;
         glVertex2d (x, y);
      }
   glEnd ();  
}
