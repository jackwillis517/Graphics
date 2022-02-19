/******************************************
*
* Official Name:  Jack Andrew Willis
*
* Call me: Jack
*
* E-mail:  jwilli59@syr.edu
*
* Assignment:  Assignment 2
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  February 28, 2022
*
* References:  
*
* Interactions:   
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
static int radiobuttonselected = 2;
static bool firstBoxChecked = false;
static bool secondBoxChecked = false;
static bool thirdBoxChecked = false;
static bool fourthBoxChecked = false;



//Draws the background of the control panel
void drawControlPanelBackground()
{
    // Black outline of control panel
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
        glVertex3f(15.0, 85.0, -1.0);
        glVertex3f(85.0, 85.0, -1.0);
        glVertex3f(85.0, 15.0, -1.0);
        glVertex3f(15.0, 15.0, -1.0);
    glEnd();

    // Orange background of control panel
    glColor3f(0.8392156862745098, 0.4117647058823529, 0.0549019607843137);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
        glVertex3f(15.0, 85.0, -1.001);
        glVertex3f(85.0, 85.0, -1.001);
        glVertex3f(85.0, 15.0, -1.001);
        glVertex3f(15.0, 15.0, -1.001);
    glEnd();


    // Check boxes

    // First check box
    glColor3f(0, 0, 0);
    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex3f(25.0, 70.0, -1.0);
        glVertex3f(30.0, 70.0, -1.0);
        glVertex3f(30.0, 65.0, -1.0);
        glVertex3f(25.0, 65.0, -1.0);
    glEnd();

    // Second check box
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex3f(25.0, 60.0, -1.0);
        glVertex3f(30.0, 60.0, -1.0);
        glVertex3f(30.0, 55.0, -1.0);
        glVertex3f(25.0, 55.0, -1.0);
    glEnd();

    // Third check box
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex3f(25.0, 50.0, -1.0);
        glVertex3f(30.0, 50.0, -1.0);
        glVertex3f(30.0, 45.0, -1.0);
        glVertex3f(25.0, 45.0, -1.0);
    glEnd();

    // Fourth check box
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex3f(25.0, 40.0, -1.0);
        glVertex3f(30.0, 40.0, -1.0);
        glVertex3f(30.0, 35.0, -1.0);
        glVertex3f(25.0, 35.0, -1.0);
    glEnd();
    
    // ---------------------------------------------------------------------------------------------------


    // Radio Buttons

    // First radio button click box ------------------------------------------------ 1
    /*  glVertex3f(60.0, 70.0, -1.0);
        glVertex3f(65.0, 70.0, -1.0);
        glVertex3f(65.0, 65.0, -1.0);
        glVertex3f(60.0, 65.0, -1.0);*/

    glLineWidth(4.0);

    // First radio button 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
        if (radiobuttonselected == 1) {
            glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
        }
        else {
            glColor3f(0.392156862745098, 0.3725490196078431, 0.3490196078431373);
        }
        glVertex3f(62.5, 67.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 67.5, -1);
        }
    glEnd();

    // First radio button outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
        glVertex3f(62.5, 67.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 67.5, -1);
        }
    glEnd();

    // Second radio button click box ------------------------------------------------ 2
    /*  glVertex3f(60.0, 60.0, -1.0);
        glVertex3f(65.0, 60.0, -1.0);
        glVertex3f(65.0, 55.0, -1.0);
        glVertex3f(60.0, 55.0, -1.0);*/

    // Second radio button
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
        if (radiobuttonselected == 2) {
            glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
        }
        else {
            glColor3f(0.392156862745098, 0.3725490196078431, 0.3490196078431373);
        }
        glVertex3f(62.5, 57.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 57.5, -1);
        }
    glEnd();

    // Second radio button outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
        glVertex3f(62.5, 57.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 57.5, -1);
        }
    glEnd();

    // Third radio button click box ------------------------------------------------ 3
   /*   glVertex3f(60.0, 50.0, -1.0);
        glVertex3f(65.0, 50.0, -1.0);
        glVertex3f(65.0, 45.0, -1.0);
        glVertex3f(60.0, 45.0, -1.0);*/

    // Third radio button
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
        if (radiobuttonselected == 3) {
            glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
        }
        else {
            glColor3f(0.392156862745098, 0.3725490196078431, 0.3490196078431373);
        }
        glVertex3f(62.5, 47.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 47.5, -1);
        }
    glEnd();

    // Third radio button outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
        glVertex3f(62.5, 47.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 47.5, -1);
        }
    glEnd();

    // Fourth radio button click box ------------------------------------------------ 4
    /*  glVertex3f(60.0, 40.0, -1.0);
        glVertex3f(65.0, 40.0, -1.0);
        glVertex3f(65.0, 35.0, -1.0);
        glVertex3f(60.0, 35.0, -1.0);*/

    // Fourth radio button
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
        if (radiobuttonselected == 4) {
            glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
        }
        else {
            glColor3f(0.392156862745098, 0.3725490196078431, 0.3490196078431373);
        }
        glVertex3f(62.5, 37.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 37.5, -1);
        }
    glEnd();
    
    // Fourth radio button outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
        glVertex3f(62.5, 37.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 37.5, -1);
        }
    glEnd();

    // Fifth radio button click box ------------------------------------------------ 5
    /*  glVertex3f(60.0, 30.0, -1.0);
        glVertex3f(65.0, 30.0, -1.0);
        glVertex3f(65.0, 25.0, -1.0);
        glVertex3f(60.0, 25.0, -1.0);*/

    // Fifth radio button
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    if (radiobuttonselected == 5) {
        glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
    }
    else {
        glColor3f(0.392156862745098, 0.3725490196078431, 0.3490196078431373);
    }
    glVertex3f(62.5, 27.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) +27.5, -1);
        }
    glEnd();

    // Fifth radio button outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
        glVertex3f(62.5, 27.5, -1.0);
        for (int j = 0; j <= 150; j++)
        {
            glVertex3f(2.5 * cos((float)(j) / 50 * 2 * PI) + 62.5, 2.5 * sin((float)(j) / 50 * 2 * PI) + 27.5, -1);
        }
    glEnd();

    // ---------------------------------------------------------------------------------------------------
}

void writeBitmapString(void* font, const char* string)
{
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawControlPanelText()
{
    glColor3f(0, 0, 0);

    // Check boxes title
    glRasterPos3f(29.0, 75.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Stellar Objects");

    // Radio buttons title
    glRasterPos3f(62.0, 75.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Moon Phase");

    // First check box text
    glRasterPos3f(32.0, 67.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Space Station");

    // Second check box text
    glRasterPos3f(32.0, 57.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Alien Ship");

    // Third check box text
    glRasterPos3f(32.0, 47.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Jupiter");

    // Fourth check box text
    glRasterPos3f(32.0, 37.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Ursa Major");

    // First radio button text
    glRasterPos3f(68.0, 67.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "New");

    // Second radio button text
    glRasterPos3f(68.0, 57.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Crescent");

    // Third radio button text
    glRasterPos3f(68.0, 47.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Half");

    // Fourth radio button text
    glRasterPos3f(68.0, 37.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Gibbous");

    // Fifth radio button text
    glRasterPos3f(68.0, 27.0, -1.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Full");
}

void drawFirstCheck()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(4.0);
    glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
    glBegin(GL_LINES);
        glVertex3f(26, 69, -1.0);
        glVertex3f(29, 66, -1.0);
        glVertex3f(26, 66, -1.0);
        glVertex3f(29, 69, -1.0);
    glEnd();
}

void drawSecondCheck()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(4.0);
    glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
    glBegin(GL_LINES);
        glVertex3f(26, 59, -1.0);
        glVertex3f(29, 56, -1.0);
        glVertex3f(26, 56, -1.0);
        glVertex3f(29, 59, -1.0);
    glEnd();
}

void drawThirdCheck()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(4.0);
    glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
    glBegin(GL_LINES);
        glVertex3f(26, 49, -1.0);
        glVertex3f(29, 46, -1.0);
        glVertex3f(26, 46, -1.0);
        glVertex3f(29, 49, -1.0);
    glEnd();
}

void drawFourthCheck()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(4.0);
    glColor3f(0.0745098039215686, 0.0588235294117647, 0.5647058823529412);
    glBegin(GL_LINES);
        glVertex3f(26, 39, -1.0);
        glVertex3f(29, 36, -1.0);
        glVertex3f(26, 36, -1.0);
        glVertex3f(29, 39, -1.0);
    glEnd();
}

// Mouse callback routine.
void MouseControl(int button, int state, int x, int y)
{
    int xMouse, yMouse;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xMouse = x / 7;
        yMouse = (700 - y) / 7;

        // Check boxes controller
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 65 && yMouse <= 70)
        {
            if (firstBoxChecked)
            {
                firstBoxChecked = false;
            }
            else {
                firstBoxChecked = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 55 && yMouse <= 60)
        {
            if (secondBoxChecked)
            {
                secondBoxChecked = false;
            }
            else {
                secondBoxChecked = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 45 && yMouse <= 50)
        {
            if (thirdBoxChecked)
            {
                thirdBoxChecked = false;
            }
            else {
                thirdBoxChecked = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 35 && yMouse <= 40)
        {
            if (fourthBoxChecked)
            {
                fourthBoxChecked = false;
            }
            else {
                fourthBoxChecked = true;
            }
        }

        // Radio buttons controller
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 65 && yMouse <= 70) radiobuttonselected = 1;
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 55 && yMouse <= 60) radiobuttonselected = 2;
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 45 && yMouse <= 50) radiobuttonselected = 3;
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 35 && yMouse <= 40) radiobuttonselected = 4;
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 25 && yMouse <= 30) radiobuttonselected = 5;

        glutPostRedisplay();
    }
}


void printInstructions() 
{
    cout << "Interaction:" << endl;
    cout << "Press n for new moon" << endl;
    cout << "Press c for crescent moon" << endl;
    cout << "Press h for half moon" << endl;
    cout << "Press g for gibbous moon" << endl;
    cout << "Press f for full moon" << endl;
}


// Drawing routine.
void drawScene(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glFrustum(0.0, 100.0, 0.0, 100.0, 1.0, 50.0);

  drawControlPanelBackground();
  drawControlPanelText();
  if (firstBoxChecked) drawFirstCheck();
  if (secondBoxChecked) drawSecondCheck();
  if (thirdBoxChecked) drawThirdCheck();
  if (fourthBoxChecked) drawFourthCheck();

  glutSwapBuffers(); //instead of glFlush, double buffer
}


void setup(void) 
{
  //Blue gray background
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  /*glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);*/
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(0.0, 100.0, 0.0, 100.0, 1.0, 50.0);
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

    case 'n':
        radiobuttonselected = 1;
        glutPostRedisplay();
        break;

    case 'c':
        radiobuttonselected = 2;
        glutPostRedisplay();
        break;

    case 'h':
        radiobuttonselected = 3;
        glutPostRedisplay();
        break;

    case 'g':
        radiobuttonselected = 4;
        glutPostRedisplay();
        break;

    case 'f':
        radiobuttonselected = 5;
        glutPostRedisplay();
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
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Control Panel");
  setup(); 
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMouseFunc(MouseControl);
  glutMainLoop(); 
  
  return 0;  
}

