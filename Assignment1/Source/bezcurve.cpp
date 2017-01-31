#include <GL/glut.h>
void draw_bezcurve(int nCtrlPoints,float ctrlpoints[][3])
{
   int i;
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, nCtrlPoints,&ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();   
}
