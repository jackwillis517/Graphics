/******************************************
*
* Official Name:  Jack Andrew Willis
*
* Call me: Jack
*
* E-mail:  jwilli59@syr.edu
*
* Assignment:  Assignment 1
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  February 14, 2022
*
* References:  simplePerson.cpp, imagecolorpicker.com
*
* Interactions:   a spawns the Ancient One
*                 p activated the portal
*                 v changes projection mode from ortho to frustum
*******************************************/


#include <cmath>
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
static float cx=25.0, cy=18.0, cz=0.5;  //center of head
static float cx2 = 45.0, cy2 = 22.0, cz2 = 0.2;  //center of head
static float bodylength = 4.0;
static float bodylength2 = 6.0;
static bool orthoProj = true;
static bool portalsActive = false;
static bool spawnAncientOne = false;

static float vertices[] =
{
    70, 20, .5,
    65, 10, .5,
    80, 20, .5,
    75, 10, .5,
    80, 30, .5,
    75, 25, .5,
    70, 30, .5,
    65, 25, .5,
    70, 20, .5,
    65, 10, .5,
    75, 10, .5
};

static float colors[] =
{
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    0.7450980392157, 0.7450980392157, 0.7450980392157,
    0.7450980392157, 0.7450980392157, 0.7450980392157,
    0.2156862745098039, 0.2431372549019608, 0.2627450980392157,
    1.2156862745098039, 0.2431372549019608, 0.2627450980392157
};

void drawCube()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 11; i++) glArrayElement(i);
    glEnd();
    glDisable(GL_DEPTH_TEST);
}

void drawHead2()
{
    glEnable(GL_DEPTH_TEST);
    int j;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(cx2, cy2, cz2);
    for (j = 0; j <= nv; j++)
    {
        glVertex3f(r * cos((float)(j) / nv * 2 * PI) + cx2, r * sin((float)(j) / nv * 2 * PI) + cy2, cz2);
    }
    glEnd();


    glDisable(GL_DEPTH_TEST);

}

void drawStickBody2()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.93, 0.8196078431372549, 0.0156862745098039);
    glBegin(GL_LINES);
        glVertex3f(cx2, cy2 - r, cz2);
        glVertex3f(cx2, cy2 - r - bodylength2, cz2);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
}

void drawStickArms2()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
        glVertex3f(cx2, cy2 - r - .2 * bodylength2, cz2);
        glVertex3f(cx2 - 1, cy2 - r - 1.2 * bodylength2, cz2);
        glVertex3f(cx2, cy2 - r - .2 * bodylength2, cz2);
        glVertex3f(cx2 + 1, cy2 - r - 1.2 * bodylength2, cz2);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
}

void drawStickArms2Scared()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
        glVertex3f(cx2, cy2 - r - .2 * bodylength2, cz2);
        glVertex3f(cx2 - 3, cy2 - r * bodylength2 + 6, cz2);
        glVertex3f(cx2, cy2 - r - .2 * bodylength2, cz2);
        glVertex3f(cx2 + 3, cy2 - r * bodylength2 + 6, cz2);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
}

void drawStickLegs2()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
        glVertex3f(cx2, cy2 - r - bodylength2, cz);
        glVertex3f(cx2 - 1, cy2 - r - bodylength2 - 6, cz2);
        glVertex3f(cx2, cy2 - r - bodylength2, cz2);
        glVertex3f(cx2 + 1, cy2 - r - bodylength2 - 6, cz2);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
}

// From simplePerson.cpp
void drawHead()
{
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  int j;
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f(cx,cy,cz);
  for(j = 0; j <= nv; j++)
  {
      glVertex3f(r * cos( (float)(j)/nv * 2*PI ) +cx, r * sin( (float)(j)/nv * 2*PI )+cy, cz);
  }
  glEnd();


  glDisable(GL_DEPTH_TEST);
  
}

// From simplePerson.cpp
void drawStickBody()
{
  glEnable(GL_DEPTH_TEST);
  glLineWidth(5.0);
  glColor3f(0.9176470588235294, 0.0156862745098039, 0.93);
  glBegin(GL_LINES);
    glVertex3f(cx,cy-r,cz);
    glVertex3f(cx,cy-r-bodylength,cz);
  glEnd();
  glDisable(GL_DEPTH_TEST);
}

// From simplePerson.cpp
void drawStickArms()
{
  glEnable(GL_DEPTH_TEST);
  glLineWidth(5.0);
  glColor3f(0.3,0.3,1.0);
  glBegin(GL_LINES);
    glVertex3f(cx,cy-r-.2*bodylength,cz);
    glVertex3f(cx-1,cy-r-1.2*bodylength ,cz);
    glVertex3f(cx,cy-r-.2*bodylength,cz);
    glVertex3f(cx+1,cy-r-1.2*bodylength ,cz);
  glEnd();
  glDisable(GL_DEPTH_TEST);
}

// From simplePerson.cpp
void drawStickLegs()
{
  glEnable(GL_DEPTH_TEST);
  glLineWidth(5.0);
  glColor3f(0.3, 0.3, 1.0);
  glBegin(GL_LINES);
    glVertex3f(cx,cy-r-bodylength,cz);
    glVertex3f(cx-1,cy-r-bodylength-6,cz);
    glVertex3f(cx,cy-r-bodylength,cz);
    glVertex3f(cx+1,cy-r-bodylength-6,cz);
  glEnd();
  glLineWidth(1.0);
  glColor3f(0.0,0.0,0.0);
  glDisable(GL_DEPTH_TEST);
}

void drawSphere() 
{
    glColor3f(1, 1, 0);
    glutWireSphere(15.0, 10, 8);
}



void drawBackground()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.5568627450980392, 0.5882352941176471, 0.6117647058823529);

    float x1 = -16.0;
    float y1 = 10.0;
    float x2 = 116.0;
    float y2 = 115.0;
    float z = -30;

    for (int i = 0; i <= 32; i++) {
        if (i == 32) {
            glColor3f(1, 1, 1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_POLYGON);
            glVertex3f(x1, y1, z);
            glVertex3f(50.0, y2, z);
            glVertex3f(x2, y1, z);
        glEnd();
        glDisable(GL_DEPTH_TEST);
        x1 += 2;
        x2 -= 2;
        y1 += 1;
        y2 -= 2;
        z -= .5;
    }
    //All 10 pillers/rocks in the background are made from polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(12.0, 100.0, 0);
        glVertex3f(26.0, 100.0, 0);
        glVertex3f(26.0, 89.0, 0);
        glVertex3f(12.0, 89.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(14.0, 89.0, 0);
        glVertex3f(22.5, 89.0, 0);
        glVertex3f(22.5, 65.0, 0);
        glVertex3f(14.0, 65.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.2156862745098039, 0.2431372549019608, 0.2627450980392157);
    glBegin(GL_POLYGON);
        glVertex3f(9.0, 75.0, 0);
        glVertex3f(14.0, 75.0, 0);
        glVertex3f(14.0, 35.0, 0);
        glVertex3f(9.0, 35.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 100.0, 0);
        glVertex3f(9.0, 100.0, 0);
        glVertex3f(9.0, 30.0, 0);
        glVertex3f(0.0, 30.0, 0);
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
        glVertex3f(62.0, 45.0, 0);
        glVertex3f(67.0, 45.0, 0);
        glVertex3f(67.0, 36.0, 0);
        glVertex3f(62.0, 36.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.2156862745098039, 0.2431372549019608, 0.2627450980392157);
    glBegin(GL_POLYGON);
        glVertex3f(75.0, 47.0, 0);
        glVertex3f(70.0, 47.0, 0);
        glVertex3f(70.0, 38.0, 0);
        glVertex3f(75.0, 38.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 100.0, 0);
        glVertex3f(80.0, 100.0, 0);
        glVertex3f(80.0, 98.0, 0);
        glVertex3f(100.0, 98.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 100.0, 0);
        glVertex3f(95.0, 100.0, 0);
        glVertex3f(95.0, 35.0, 0);
        glVertex3f(100.0, 35.0, 0);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 100.0, 0);
        glVertex3f(95.0, 100.0, 0);
        glVertex3f(95.0, 35.0, 0);
        glVertex3f(100.0, 35.0, 0);
    glEnd();
}

void drawTheAncientOnesHead()
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(50, 42, -25);
        glVertex3f(54, 42, -25);
        glVertex3f(52, 46, -25);
    glEnd();


    glDisable(GL_DEPTH_TEST);

}

void drawTheAncientOnesBody()
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.93, 0.3058823529411765, 0.0156862745098039);
    glBegin(GL_POLYGON);
        glVertex3f(48, 42, -25);
        glVertex3f(56, 42, -25);
        glVertex3f(52, 36, -25);
    glEnd();
    glDisable(GL_DEPTH_TEST);
}

void drawTheAncientOnesArms()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
        glVertex3f(52, 42, -26); 
        glVertex3f(45, 39, -26);
        glVertex3f(52, 40, -26);
        glVertex3f(59, 42, -26);
        glVertex3f(59, 42, -26);
        glVertex3f(61, 45, -26);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}

void drawTheAncientOnesArms2()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
    glVertex3f(52, 42, -26);
    glVertex3f(45, 39, -26);
    glVertex3f(52, 40, -26);
    glVertex3f(59, 42, -26);
    glVertex3f(59, 42, -26);
    glVertex3f(59, 45, -26);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}


void drawTheAncientOnesLegs()
{
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0.3, 0.3, 1.0);
    glBegin(GL_LINES);
        glVertex3f(52, 38, -26);
        glVertex3f(49, 35, -26);
        glVertex3f(49, 35, -26);
        glVertex3f(49, 30, -26);

        glVertex3f(52, 38, -26);
        glVertex3f(55, 35, -26);
        glVertex3f(55, 35, -26);
        glVertex3f(55, 30, -26);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}

void drawForground()
{
    // Polygon used to create the ledge the portal is sitting on
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.1568627450980392, 0.1725490196078431, 0.1843137254901961);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 45.0, 0);
        glVertex3f(40.0, 45.0, 0);
        glVertex3f(40.0, 17.0, 0);
        glVertex3f(0.0, 17.0, 0);
    glEnd();

    // Triangle Strip used for ledge behind hollow cube
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(62, 36, 0);
        glVertex3f(62, 15, 0);
        glVertex3f(70, 38, 0);
        glVertex3f(70, 15, 0);
        glVertex3f(80, 39, 0);
        glVertex3f(80, 15, 0);
        glVertex3f(100, 38, 0);
        glVertex3f(100, 15, 0);
    glEnd();

    // Triangle Fan used for background of portals, for loop references simplePerson.cpp
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(20, 47, -1);
        for (int j = 0; j <= 50; j++)
        {
            glVertex3f(13 * cos((float)(j) / 50 * 2 * PI) + 20, 13 * sin((float)(j) / 50 * 2 * PI) + 52, -1);
        }
    glEnd();

    // Triangle Fan used for portals, for loop references simplePerson.cpp
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
        if (portalsActive) {
            glColor3f(0.24313725490196078431372549019608, 0.11764705882352941176470588235294, 0.69803921568627450980392156862745);
        }
        else {
            glColor3f(0, 0, 0);
        }
        glVertex3f(20, 47, -.5);
        for (int j = 0; j <= 50; j++)
        {
            glVertex3f(12 * cos((float)(j) / 50 * 2 * PI) + 20, 12 * sin((float)(j) / 50 * 2 * PI) + 52, -1);
        }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(0, 20, .2);
        glVertex3f(100, 20, .2);
        glVertex3f(100, 0, .2);
        glVertex3f(0, 0, .2);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.203921568627451, 0.2156862745098039, 0.2235294117647059);
    glBegin(GL_POLYGON);
        glVertex3f(0, 32, -1);
        glVertex3f(100, 32, -1);
        glVertex3f(100, 30, -1);
        glVertex3f(0, 30, -1);
        glEnd();
    glDisable(GL_DEPTH_TEST);
}

void writeBitmapString(void* font, const char* string)
{
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawPortalText()
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(1, 0, 0);
    glRasterPos3f(3.0, 3.0, .7);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Portal Activated!");
    glDisable(GL_DEPTH_TEST);

}

void drawAncientOneText()
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(1, 0, 0);
    glRasterPos3f(3.0, 5.0, .7);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "Ancient One Awoken!");
    glDisable(GL_DEPTH_TEST);

}

void printInstructions() 
{
    cout << "Interaction:" << endl;
    cout << "Press p to activate portal" << endl;
    cout << "Press v to change projection mode" << endl;
    cout << "Press a to summon the Ancient One" << endl;
}

// Cylinder with triangle strip, modified for loop to draw heads from simplePerson.cpp
void drawCylinderBody() 
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= 50; j++){
            if (j % 2 == 0) {
                glVertex3f(1 * cos((float)(j) / 50 * 2 * PI) + 55, 2 * sin((float)(j) / 50 * 2 * PI) + 25, .8);
            }
            else {
                glVertex3f(1 * cos((float)(j) / 50 * 2 * PI) + 55, 2 * sin((float)(j) / 50 * 2 * PI) + 20, .8);
            }

        }
    glEnd();
}

void drawSquareHead() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(54, 28, .9);
        glVertex3f(56, 28, .9);
        glVertex3f(56, 26, .9);
        glVertex3f(54, 26, .9);
    glEnd();
    glDisable(GL_DEPTH_TEST);
}

void drawCylinderArms() {
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
      glVertex3f(55, 26, .8);
      glVertex3f(57, 21, .8);
      glVertex3f(55, 26, .8);
      glVertex3f(53, 21, .8);
   glEnd();
   glLineWidth(1.0);
   glDisable(GL_DEPTH_TEST);
}

void drawCylinderArmsScared() {
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(55, 22, .8);
        glVertex3f(58, 27, .8);
        glVertex3f(55, 22, .8);
        glVertex3f(52, 27, .8);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}

void drawCylinderLegs() {
    glEnable(GL_DEPTH_TEST);
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(55, 21, .8);
        glVertex3f(57, 15, .8);
        glVertex3f(55, 21, .8);
        glVertex3f(53, 15, .8);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_DEPTH_TEST);
}

// Drawing routine.
void drawScene(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (orthoProj) {
      glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 50.0);
  }
  else {
      glFrustum(0, 100, 0, 100, 1, 50);
  }

  if (portalsActive) {
      drawPortalText();
  }

  if (spawnAncientOne) {
      drawHead2();
      drawStickBody2();
      drawStickArms2Scared();
      drawStickLegs2();

      drawAncientOneText();
      drawTheAncientOnesHead();
      drawTheAncientOnesBody();
      drawTheAncientOnesLegs();
      drawTheAncientOnesArms();

      drawCylinderBody();
      drawSquareHead();
      drawCylinderArmsScared();
      drawCylinderLegs();
         
  } else {
      drawHead2();
      drawStickBody2();
      drawStickArms2();
      drawStickLegs2();

      drawCylinderBody();
      drawSquareHead();
      drawCylinderArms();
      drawCylinderLegs();
  }

  

  drawCube();

  drawHead();
  drawStickBody();
  drawStickArms();
  drawStickLegs();

  drawBackground();
  drawForground();
  
  glutSwapBuffers(); //instead of glFlush, double buffer
}


void setup(void) 
{
  //Blue gray background
  glClearColor(0.20784313725490, 0.262745098039215, 0.298039215686274, 0.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (orthoProj) {
      glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 50.0);
  }
  else {
      glFrustum(0, 100, 0, 100, 1, 50);
  }
  /*glMatrixMode(GL_MODELVIEW);*/
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
  {
    case 27:
      exit(0);
      break;

    case 'v':
        if (orthoProj) {
            orthoProj = false;
            glutPostRedisplay();
        }
        else {
            orthoProj = true;
            glutPostRedisplay();
        }
        break;

    case 'p':
        if (portalsActive) {
            portalsActive = false;
            glutPostRedisplay();
        }
        else {
            portalsActive = true;
            glutPostRedisplay();
            
        }
        break;

    case 'a':
        if (spawnAncientOne) {
            spawnAncientOne = false;
            glutPostRedisplay();
        }
        else {
            spawnAncientOne = true;
            glutPostRedisplay();

        }
        break;

    default:
      break;
  }
}



// Main routine.
int main(int argc, char **argv) 
{
  printInstructions();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Ancient Cavern");
  setup(); 
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMainLoop(); 
  
  return 0;  
}

