#include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "../include/bezcurve.h"
#include "../include/lagrange.h"

using namespace std;


static GLfloat spin=0.0;
static GLfloat zoom=1.0;
static GLfloat dx=0.0,dy=0.0;

//necessary for picking points
GLdouble pos3D_x, pos3D_y=20.0, pos3D_z ;
GLdouble projection_matrix[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1} ;
GLdouble modelview_matrix[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1} ;
GLint viewport[4] = {0,0,0,0}; 


GLint mode=0;
//for left click translation
GLint mouse_x1, mouse_y1,mouse_x2, mouse_y2;
GLint count=1;

//for right click picking
GLint mouse_x, mouse_y ;


int lc1=lcurve1;
int lc2=lcurve2;
int lc3=lcurve3;
int lc4=lcurve4;

int bc1=bcurve1;
int bc2=bcurve2;
int bc3=bcurve3;
int bc4=bcurve4;
int bc5=bcurve5;
int bc6=bcurve1;
int bc7=bcurve2;
int bc8=bcurve3;
int bc9=bcurve4;
int bc10=bcurve5;

void delete_display_lag();
void delete_display_bez();

void delete_vertex_lag(int,int);
void delete_vertex_bez(int,int);

void init(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-350.0,350.0,-350.0,350.0,-350.0,350.0);	
}

void pickpoint(void) 
{
  glGetDoublev(GL_PROJECTION_MATRIX, projection_matrix) ;
  glGetIntegerv(GL_VIEWPORT, viewport) ;
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix) ;
  gluUnProject(mouse_x, mouse_y, 0,
	modelview_matrix, projection_matrix, viewport,
	&pos3D_x, &pos3D_y, &pos3D_z);
}


void read_bez_points()
{
	float a,xshift=180.0,yshift=110.0;
	float x2shift=70.0;
	fstream file("../data/bez.txt", ios_base::in);
	
	//Taking input from file to every curve array.
	for(int i= 0; i<bcurve1;i++)
    {
		file>>a;
    	c1[i][0]=a-xshift;
		c1[i][2]=0.0;
		c6[i][0]=a+x2shift;
		c6[i][2]=0.0;
    
    }
    for(int i= 0; i<bcurve1;i++)
    {
		file >> a;
    	c1[i][1]=a-yshift;
    	c6[i][1]=a-yshift;	
	}
	for(int i= 0;i<bcurve2;i++)
    {
		file>>a;
    	c2[i][0]=a-xshift;
		c2[i][2]=0.0;
		c7[i][0]=a+x2shift;
		c7[i][2]=0.0;
    
    }
    for(int i= 0; i<bcurve2;i++)
    {
		file >> a;
    	c2[i][1]=a-yshift;
		c7[i][1]=a-yshift;
	}
	for(int i= 0;i<bcurve3;i++)
    {
		file>>a;
    	c3[i][0]=a-xshift;
		c3[i][2]=0.0;
		c8[i][0]=a+x2shift;
		c8[i][2]=0.0;
    
    }
    for(int i= 0; i<bcurve3;i++)
    {
		file >> a;
    	c3[i][1]=a-yshift;
    	c8[i][1]=a-yshift;
	}
	for(int i= 0;i<bcurve4;i++)
    {
		file>>a;
    	c4[i][0]=a-xshift;
		c4[i][2]=0.0;
		c9[i][0]=a+x2shift;
		c9[i][2]=0.0;
    
    }
    for(int i= 0; i<bcurve4;i++)
    {
		file >> a;
    	c4[i][1]=a-yshift;
    	c9[i][1]=a-yshift;
	}
    for(int i= 0;i<bcurve5;i++)
    {
		file>>a;
    	c5[i][0]=a-xshift;
		c5[i][2]=0.0;
		c10[i][0]=a+x2shift;
		c10[i][2]=0.0;
    
    }
    for(int i= 0; i<bcurve5;i++)
    {
		file >> a;
    	c5[i][1]=a-yshift;
    	c10[i][1]=a-yshift;
	}
	file.close();
}		
void read_lag_points()
{
	float a,xshift=82.43,yshift=169.2;
	
	fstream file("../data/lag.txt", ios_base::in);
	
	//Taking input from file to every curve array.
	for(int i= 0; i<lcurve1;i++)
    {
		file>>a;
    	c1x[i]=a-xshift;
    }
    for(int i= 0; i<lcurve1;i++)
    {
		file >> a;
		c1y[i]=a-yshift;
    }
    
    for(int i= 0; i<lcurve2;i++)
    {
		file>>a;
    	c2x[i]=a-xshift;
    }
    for(int i= 0; i<lcurve2;i++)
    {
		file >> a;
		c2y[i]=a-yshift;
    }
    
    for(int i= 0; i<lcurve3;i++)
    {
		file>>a;
    	c3x[i]=a-xshift;
    }
    for(int i= 0; i<lcurve3;i++)
    {
		file >> a;
		c3y[i]=a-yshift;
    }
    
    for(int i= 0; i<lcurve4;i++)
    {
		file>>a;
    	c4x[i]=a-xshift;
    }
    for(int i= 0; i<lcurve4;i++)
    {
		file >> a;
		c4y[i]=a-yshift;
    }
    file.close();
}	

void draw_points_bez(int number_of_points,float c[][3])
{
		glPointSize(3.0);
		glBegin(GL_POINTS);
			for(int i=0;i<number_of_points;i++)
			{
				glVertex2d(c[i][0],c[i][1]);	
			}
		glEnd();
}
void draw_points_lag(float c1x[],float c1y[],int number_of_points)
{
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			for(int i=0;i<number_of_points;i++)
			{
				glVertex2d(c1x[i],c1y[i]);	
			}
		glEnd();
}

void Bezier()
{	//read points from the file
	read_bez_points();
	
	//set color
	glColor3f(0.0,1.0,0.0);
	
	//render all bezier curves 
	draw_bezcurve(bcurve1,c1);
	draw_points_bez(bcurve1,c1);
	
	draw_bezcurve(bcurve2,c2);
	draw_points_bez(bcurve2,c2);
	
	draw_bezcurve(bcurve3,c3);
	draw_points_bez(bcurve3,c3);
	
	draw_bezcurve(bcurve4,c4);
	draw_points_bez(bcurve4,c4);
	
	draw_bezcurve(bcurve5,c5);
	draw_points_bez(bcurve5,c5);
	
	glColor3f(1.0,0.0,0.0);
	
	draw_bezcurve(bcurve1,c6);
	draw_points_bez(bcurve1,c6);
	
	draw_bezcurve(bcurve2,c7);
	draw_points_bez(bcurve2,c7);
	
	draw_bezcurve(bcurve3,c8);
	draw_points_bez(bcurve3,c8);
	
	draw_bezcurve(bcurve4,c9);
	draw_points_bez(bcurve4,c9);
	
	draw_bezcurve(bcurve5,c10);
	draw_points_bez(bcurve5,c10);
	
}
void Lagrange()
{	//read points from the file & plot them
	read_lag_points();
	
	//render all lagrange curves
	Lagrange_interpolate(c1x,c1y,lcurve1);
	
	Lagrange_interpolate(c2x,c2y,lcurve2);
	
	Lagrange_interpolate(c3x,c3y,lcurve3);
	
	Lagrange_interpolate(c4x,c4y,lcurve4);
}

void axes()
{//Drawing reference axis
	glPushMatrix();
		glLoadIdentity();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(350.0,0.0,0);
		glEnd();	
	
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,350.0,0.0);
		glEnd();
	glPopMatrix();
}

void display()
{
	if(mode==0)
	{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	axes();	
	glPushMatrix();
		glRotatef(spin,0.0,0.0,1.0);
		glScalef(zoom,zoom,1.0);
		glTranslatef(dx,dy,0.0);
		Bezier();
		Lagrange();
	glPopMatrix();	
	glPointSize(3.0);	
	draw_points_lag(c1x,c1y,lcurve1);	
	draw_points_lag(c2x,c2y,lcurve2);	
	draw_points_lag(c3x,c3y,lcurve3);	
	draw_points_lag(c4x,c4y,lcurve4);
	}
	else
	{ 
		if(mode==1)
			delete_display_lag();	
		else
			delete_display_bez();	
	}
glutSwapBuffers();	
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-350.0, 350.0, -350.0, 350.0, -350.0, 350.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void spinDisplay(void)
{
   spin = spin + 1.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}
void oppspinDisplay(void)
{
   spin = spin - 1.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

//keyboard functions
void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'l':
				mode=0;
				spinDisplay();
				break;
		case 'r':
				mode=0;
				oppspinDisplay();
				break;
		case '+':
				mode=0;
				zoom=zoom+0.2;
				glutPostRedisplay();
				break;
		case '-':
				mode=0;
				zoom=zoom-0.1;
				if(zoom	<0.0)
					zoom=1.0;	
				glutPostRedisplay();
				break;	
		case 'd':
				mode=1;
				glutPostRedisplay();
				break;
		case 'b':
				mode=2;
				glutPostRedisplay();
				break;
		default:
		break;
	}
}

//mouse handling
void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(count==1)
		{
			mouse_x1=x;
			mouse_y1=-y;
			count++;
		}
		else 
		{
			mouse_x2=x;
			mouse_y2=-y;
			count=1;
			dx=mouse_x2-mouse_x1;
			dy=mouse_y2-mouse_y1;
			glutPostRedisplay();
		}	
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		mouse_x=x;
		mouse_y=y;
		pickpoint();	
		mouse_x=pos3D_x;
		mouse_y=-pos3D_y;
		//cout<<"x:"<<mouse_x<<" y:"<<mouse_y<<endl;
		if(mode==1)
		{
				delete_vertex_lag(mouse_x,mouse_y);	
				glutPostRedisplay();
		}
		if(mode==2)
		{
				delete_vertex_bez(mouse_x,mouse_y);
				glutPostRedisplay();
		}
	}
				
}

//main function
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,700);
	glutCreateWindow("CURVES");
	init();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

//Reconstruct lagrange after delete
void delete_display_lag()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	axes();	
	Lagrange_interpolate(c1x,c1y,lc1);
	Lagrange_interpolate(c2x,c2y,lc2);
	Lagrange_interpolate(c3x,c3y,lc3);
	Lagrange_interpolate(c4x,c4y,lc4);
	glPointSize(5.0);
	draw_points_lag(c1x,c1y,lc1);	
	draw_points_lag(c2x,c2y,lc2);	
	draw_points_lag(c3x,c3y,lc3);	
	draw_points_lag(c4x,c4y,lc4);
}
//Reconstruct bezier after delete
void delete_display_bez()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	axes();	
	glColor3f(0.0,1.0,0.0);
	//render all bezier curves 
	draw_bezcurve(bc1,c1);
	draw_points_bez(bc1,c1);
			
	draw_bezcurve(bc2,c2);
	draw_points_bez(bc2,c2);
	
	draw_bezcurve(bc3,c3);
	draw_points_bez(bc3,c3);
	
	draw_bezcurve(bc4,c4);
	draw_points_bez(bc4,c4);
	
	draw_bezcurve(bc5,c5);
	draw_points_bez(bc5,c5);

	glColor3f(1.0,0.0,0.0);

	draw_bezcurve(bc6,c6);
	draw_points_bez(bc6,c6);
			
	draw_bezcurve(bc7,c7);
	draw_points_bez(bc7,c7);
	
	draw_bezcurve(bc8,c8);
	draw_points_bez(bc8,c8);
	
	draw_bezcurve(bc9,c9);
	draw_points_bez(bc9,c9);
	
	draw_bezcurve(bc10,c10);
	draw_points_bez(bc10,c10);

}

//Delete Bezier Curve control points.
void delete_vertex_bez(int x,int y)
{
	int loop;
	//check for curve1
	for(loop=0;loop<bc1;loop++)
	{
		if((x<=c1[loop][0]+3 && x>=c1[loop][0]-3) &&(y<=c1[loop][1]+3 && y>=c1[loop][1]-3))  
			break;	
	}
	if(loop==bc1){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc1-1;i++)
		{
			c1[i][0]=c1[i+1][0];
			c1[i][1]=c1[i+1][1];	
		}
		bc1--;
	}
	//check for curve 2
	for(loop=0;loop<bc2;loop++)
	{
		if((x<=c2[loop][0]+3 && x>=c2[loop][0]-3) &&(y<=c2[loop][1]+3 && y>=c2[loop][1]-3))  
			break;	
	}
	if(loop==bc2){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc2-1;i++)
		{
			c2[i][0]=c2[i+1][0];
			c2[i][1]=c2[i+1][1];	
		}
		bc2--;
	}
	//check for curve 3
	for(loop=0;loop<bc3;loop++)
	{
		if((x<=c3[loop][0]+3 && x>=c3[loop][0]-3) &&(y<=c3[loop][1]+3 && y>=c3[loop][1]-3))  
			break;	
	}
	if(loop==bc3){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc3-1;i++)
		{
			c3[i][0]=c3[i+1][0];
			c3[i][1]=c3[i+1][1];	
		}
		bc3--;
	}	
	//check for curve 4
	for(loop=0;loop<bc4;loop++)
	{
		if((x<=c4[loop][0]+3 && x>=c4[loop][0]-3) &&(y<=c4[loop][1]+3 && y>=c4[loop][1]-3))  
			break;	
	}
	if(loop==bc4){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc4-1;i++)
		{
			c4[i][0]=c4[i+1][0];
			c4[i][1]=c4[i+1][1];	
		}
		bc4--;
	}		
	//check for curve 5
	for(loop=0;loop<bc5;loop++)
	{
		if((x<=c5[loop][0]+3 && x>=c5[loop][0]-3) &&(y<=c5[loop][1]+3 && y>=c5[loop][1]-3))  
			break;	
	}
	if(loop==bc5){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc5-1;i++)
		{
			c5[i][0]=c5[i+1][0];
			c5[i][1]=c5[i+1][1];	
		}
		bc5--;
	}
	//check for curve6
	for(loop=0;loop<bc6;loop++)
	{
		if((x<=c6[loop][0]+3 && x>=c6[loop][0]-3) &&(y<=c6[loop][1]+3 && y>=c6[loop][1]-3))  
			break;	
	}
	if(loop==bc6){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc6-1;i++)
		{
			c6[i][0]=c6[i+1][0];
			c6[i][1]=c6[i+1][1];	
		}
		bc6--;
	}
	//check for curve 7
	for(loop=0;loop<bc7;loop++)
	{
		if((x<=c7[loop][0]+3 && x>=c7[loop][0]-3) &&(y<=c7[loop][1]+3 && y>=c7[loop][1]-3))  
			break;	
	}
	if(loop==bc7){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc7-1;i++)
		{
			c7[i][0]=c7[i+1][0];
			c7[i][1]=c7[i+1][1];	
		}
		bc7--;
	}
	//check for curve 8
	for(loop=0;loop<bc8;loop++)
	{
		if((x<=c8[loop][0]+3 && x>=c8[loop][0]-3) &&(y<=c8[loop][1]+3 && y>=c8[loop][1]-3))  
			break;	
	}
	if(loop==bc8){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc8-1;i++)
		{
			c8[i][0]=c8[i+1][0];
			c8[i][1]=c8[i+1][1];	
		}
		bc8--;
	}	
	//check for curve 9
	for(loop=0;loop<bc9;loop++)
	{
		if((x<=c9[loop][0]+3 && x>=c9[loop][0]-3) &&(y<=c9[loop][1]+3 && y>=c9[loop][1]-3))  
			break;	
	}
	if(loop==bc9){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc9-1;i++)
		{
			c9[i][0]=c9[i+1][0];
			c9[i][1]=c9[i+1][1];	
		}
		bc9--;
	}		
	//check for curve 10
	for(loop=0;loop<bc10;loop++)
	{
		if((x<=c10[loop][0]+3 && x>=c10[loop][0]-3) &&(y<=c10[loop][1]+3 && y>=c10[loop][1]-3))  
			break;	
	}
	if(loop==bc10){}
		//cout<<"Not Found in this curve:"<<endl;
	else
	{	
		//cout<<"found at :"<<loop<<endl;
		for(int i=loop;i<bc10-1;i++)
		{
			c10[i][0]=c10[i+1][0];
			c10[i][1]=c10[i+1][1];	
		}
		bc10--;
	}						
}

//Delete Lagrange Control points.
void delete_vertex_lag(int x,int y)
{
	int loop;
	//check in curve1
		for(loop=0;loop<lc1;loop++)
		{
			if((x<=c1x[loop]+3 && x>=c1x[loop]-3) &&(y<=c1y[loop]+3 && y>=c1y[loop]-3))  
			break;
		}	
		if(loop==lc1){}
			//cout<<"Not Found in this curve:"<<endl;
		else
		{	
			//cout<<"found at :"<<loop<<endl;
			for(int i=loop;i<lc1-1;i++)
			{
				c1x[i]=c1x[i+1];
				c1y[i]=c1y[i+1];	
			}
			lc1--;
		}	
	//check in curve2
		for(loop=0;loop<lc2;loop++)
		{
			if((x<=c2x[loop]+3 && x>=c2x[loop]-3) &&(y<=c2y[loop]+3 && y>=c2y[loop]-3))  
			break;
		}	
		if(loop==lc2){}
			//cout<<"Not Found in this curve:"<<endl;
		else
		{	
			//cout<<"found at :"<<loop<<endl;
			for(int i=loop;i<lc2-1;i++)
			{
				c2x[i]=c2x[i+1];
				c2y[i]=c2y[i+1];	
			}
			lc2--;
		}	
	//check in curve3
		for(loop=0;loop<lc3;loop++)
		{
			if((x<=c3x[loop]+3 && x>=c3x[loop]-3) &&(y<=c3y[loop]+3 && y>=c3y[loop]-3))  
			break;
		}	
		if(loop==lc3){}
			//cout<<"Not Found in this curve:"<<endl;
		else
		{	
			//cout<<"found at :"<<loop<<endl;
			for(int i=loop;i<lc3-1;i++)
			{
				c3x[i]=c3x[i+1];
				c3y[i]=c3y[i+1];	
			}
			lc3--;
		}	
	//check in curve4
		for(loop=0;loop<lc4;loop++)
		{
			if((x<=c4x[loop]+3 && x>=c4x[loop]-3) &&(y<=c4y[loop]+3 && y>=c4y[loop]-3))  
			break;
		}	
		if(loop==lc4){}
			//cout<<"Not Found in this curve:"<<endl;
		else
		{	
			//cout<<"found at :"<<loop<<endl;
			for(int i=loop;i<lc3-1;i++)
			{
				c4x[i]=c4x[i+1];
				c4y[i]=c4y[i+1];	
			}
			lc4--;
		}	
}
