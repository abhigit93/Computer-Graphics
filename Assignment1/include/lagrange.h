#ifndef CURVES_H
#define CURVES_H
#include "curves.h"
#endif



GLfloat c1x[lcurve1];
GLfloat c2x[lcurve2];
GLfloat c3x[lcurve3];
GLfloat c4x[lcurve4];

GLfloat c1y[lcurve1];
GLfloat c2y[lcurve2];
GLfloat c3y[lcurve3];
GLfloat c4y[lcurve4];

double B(int n, double t);
void Lagrange_interpolate (float px[],float py[],int number_of_points);

