///////////////////////////////////////////////////////////////////////////////////////          
// simplePerson.cpp
// Author:  Baruch
//
// This program draws a person.
//
// 
/////////////////////////////////////////////////////////////////////////////////////// 

#include <cmath>
  //sin, cos
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

using namespace std;

// Globals.
static float r = 1.0; // Radius of head.
static int nv = 10;  //number of vertices for head
static float cx=20.0, cy=15.0, cz=0.0;  //center of head
static float bodylength=4.0;


void drawHead()
{
  int j;
  //draw circle head with nv vertices, center (cx,cy,xz)
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f(cx,cy,cz);
  for(j = 0; j <= nv; j++)
  {
      glVertex3f(r * cos( (float)(j)/nv * 2*PI ) +cx,
                 r * sin( (float)(j)/nv * 2*PI )+cy,
                 cz );
  }
  glEnd();
    
  
}

void drawStickBody()
{
  //draw line for body, starting at bottom of head,
    //of length bodylength
  glLineWidth(5.0);
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_LINES);
  glVertex3f(cx,cy-r,cz);
  glVertex3f(cx,cy-r-bodylength,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
  
}

void drawBackground()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.5568627450980392, 0.5882352941176471, 0.6117647058823529);
    
    float x1 = -16.0;
    float y1 = 10.0;
    float x2 = 116.0;
    float y2 = 115.0;

    for (int i = 0; i <= 32; i++) {
        if (i == 32) {
            glColor3f(1, 1, 1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glBegin(GL_POLYGON);
            glVertex3f(x1, y1, -49.0);
            glVertex3f(50.0, y2, -49.0);
            glVertex3f(x2, y1, -49.0);
        glEnd();
        x1 += 2;
        x2 -= 2;
        y1 += 1;
        y2 -= 2;
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(12.0, 100.0, -29.0);
        glVertex3f(26.0, 100.0, -29.0);
        glVertex3f(26.0, 89.0, -29.0);
        glVertex3f(12.0, 89.0, -29.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(14.0, 89.0, -29.0);
        glVertex3f(22.5, 89.0, -29.0);
        glVertex3f(22.5, 65.0, -29.0);
        glVertex3f(14.0, 65.0, -29.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.2156862745098039, 0.2431372549019608, 0.2627450980392157);
    glBegin(GL_POLYGON);
        glVertex3f(9.0, 75.0, -49.0);
        glVertex3f(14.0, 75.0, -49.0);
        glVertex3f(14.0, 35.0, -49.0);
        glVertex3f(9.0, 35.0, -49.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 100.0, -49.0);
        glVertex3f(9.0, 100.0, -49.0);
        glVertex3f(9.0, 30.0, -49.0);
        glVertex3f(0.0, 30.0, -49.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(40.0, 69.0, -35.0);
        glVertex3f(45.0, 69.0, -35.0);
        glVertex3f(45.0, 32.0, -35.0);
        glVertex3f(40.0, 32.0, -35.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(62.0, 45.0, -49.0);
        glVertex3f(67.0, 45.0, -49.0);
        glVertex3f(67.0, 36.0, -49.0);
        glVertex3f(62.0, 36.0, -49.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.2156862745098039, 0.2431372549019608, 0.2627450980392157);
    glBegin(GL_POLYGON);
        glVertex3f(75.0, 47.0, -49.0);
        glVertex3f(70.0, 47.0, -49.0);
        glVertex3f(70.0, 38.0, -49.0);
        glVertex3f(75.0, 38.0, -49.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 100.0, -49.0);
        glVertex3f(80.0, 100.0, -49.0);
        glVertex3f(80.0, 98.0, -49.0);
        glVertex3f(100.0, 98.0, -49.0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 100.0, -49.0);
        glVertex3f(95.0, 100.0, -49.0);
        glVertex3f(95.0, 35.0, -49.0);
        glVertex3f(100.0, 35.0, -49.0);
    glEnd();
}

void drawForground()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.1568627450980392, 0.1725490196078431, 0.1843137254901961);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 45.0, -49.0);
        glVertex3f(40.0, 45.0, -49.0);
        glVertex3f(40.0, 17.0, -49.0);
        glVertex3f(0.0, 17.0, -49.0);
    glEnd();
}


void drawStickArms()
{
    //draw 2 arms, attached partly down body, going down,
    //at slight angle.
  glLineWidth(5.0);
  glColor3f(0.3,0.3,1.0);
  glBegin(GL_LINES);
  glVertex3f(cx,cy-r-.2*bodylength,cz); //down 20% of body
  glVertex3f(cx-1,cy-r-1.2*bodylength ,cz);
  glVertex3f(cx,cy-r-.2*bodylength,cz); //down 20% of body
  glVertex3f(cx+1,cy-r-1.2*bodylength ,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
}

void drawStickLegs()
{
    //draw 2 legs, attached at bottom of body, going out
    //at slight angle,
  glLineWidth(5.0);
  glColor3f(1.0,0.3,0.7);
  glBegin(GL_LINES);
  glVertex3f(cx,cy-r-bodylength,cz); //down at bottom of body
  glVertex3f(cx-1,cy-r-bodylength-6,cz);
  glVertex3f(cx,cy-r-bodylength,cz); //down at bottom of body
  glVertex3f(cx+1,cy-r-bodylength-6,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
}


// Drawing routine.
void drawScene(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  drawHead();
  drawStickBody();
  drawStickArms();
  drawStickLegs();
  drawBackground();
  drawForground();
  
  glutSwapBuffers(); //instead of glFlush, double buffer
}

// Initialization routine.
void setup(void) 
{
  //white background
  glClearColor(0.20784313725490, 0.262745098039215, 0.298039215686274, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
  {
    case 27:
      exit(0);
      break;
    
    default:
      break;
  }
}



// Main routine.
int main(int argc, char **argv) 
{
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Atheon's Lair");
  setup(); 
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMainLoop(); 
  
  return 0;  
}

