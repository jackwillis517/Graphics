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
static int controlPanel, skyPanel;
static int radiobuttonselected = 2;
static bool firstBoxChecked = false;
static bool secondBoxChecked = false;
static bool thirdBoxChecked = false;
static bool fourthBoxChecked = false;
static bool spaceStation = false;
static bool alienShip = false;
static bool jupiter = false;
static bool ursaMajor = false;
static int moonAngle = -90;
static int stationAngle = 330;
static float moonSize = 5.0;


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
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Lunar Space Station");

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

float randFloat()
{
    return (300 * ((float)rand() / RAND_MAX)) + -150;
}

void drawStars()
{
    for (int i = 0; i < 1500; i++) {
        float x = (randFloat());
        float y = (randFloat());
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex3f(x, y, -49.0);
        glEnd();
    }
}

void drawMoon()
{
    glPushMatrix();
    glTranslated(0.0, 0.0, -8.0);
    glPushMatrix();
    
    // Rotate the angle of the clipping plane
    glRotated(moonAngle, 0.0, 1.0, 0.0);

    // Clip moon to half circle
    double moonEq[4] = { 1, 0, 0, 0 };
    glClipPlane(GL_CLIP_PLANE0, moonEq);
    glEnable(GL_CLIP_PLANE0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1, 25, 25);
    glDisable(GL_CLIP_PLANE0);

    // Clip shadow to half circle
    double shadowEq[4] = { -1, 0, 0, 0 };
    glClipPlane(GL_CLIP_PLANE0, shadowEq);
    glEnable(GL_CLIP_PLANE0);
    glColor3f(0.0078431372549019607843137254902, 0.066666, 0.11764705882352941176470588235294);
    glutSolidSphere(1, 25, 25);
    glDisable(GL_CLIP_PLANE0);

    glPopMatrix();
    glPopMatrix();
}

void drawJupiter()
{
    glPushMatrix();
    glColor3f(0.87843137254901960784313725490196, 0.50980392156862745098039215686275, 0.16470588235294117647058823529412);
    glTranslatef(-45, 18, -47.0);
    glRotatef(250, 0.0, 0.0, 1.0);
    glutWireSphere(1, 25, 25);
    glPopMatrix();
}

void drawSpaceStation()
{
    // Outer torus
    glPushMatrix();
    glColor3f(0.3058823529411765, 0.2823529411764706, 0.2745098039215686);
    glTranslatef(0.0, 0.0, -7.0);
    glutWireTorus(.25, 2, 25, 25);
    glPopMatrix();

    // Inner torus
    glPushMatrix();
    glColor3f(0.992156862745, 0.3098039215686275, 0.0196078431372549);
    glTranslatef(0.0, 0.0, -7.0);
    glutWireTorus(.35, .35, 25, 25);
    glPopMatrix();

    // Three connecting lines
    glLineWidth(8.0);
    glBegin(GL_LINES);
        glColor3f(0.3058823529411765, 0.2823529411764706, 0.2745098039215686);
        
        glVertex3f(0.65, -0.25, -7.0);
        glVertex3f(1.5, -1.0, -7.0);

        glVertex3f(-0.65, -0.25, -7.0);
        glVertex3f(-1.5, -1.0, -7.0);

        glVertex3f(0.0, 0.65, -7.0);
        glVertex3f(0.0, 1.72, -7.0);
    glEnd();
}

void drawUrsaMajor()
{
    glPointSize(4.0);
    glColor3f(0.9843137254901961, 0.8, 0.0235294117647059);
    glBegin(GL_POINTS);
        glVertex3f(-2.5, 6.5, -21.0);
        glVertex3f(-.4, 6.7, -21.0);
        glVertex3f(1.65, 5.75, -21.0);
        glVertex3f(3.5, 5.25, -21.0);
        glVertex3f(3.65, 4.15, -21.0);
        glVertex3f(6.5, 5.45, -21.0);
        glVertex3f(6.0, 4.05, -21.0);
    glEnd();
    glPointSize(1.0);
}

void drawMenu()
{
    int moonSizeMenu;
    moonSizeMenu = glutCreateMenu(moonMenu);
    glutAddMenuEntry("Small", 1);
    glutAddMenuEntry("Medium", 2);
    glutAddMenuEntry("Large", 3);
    glutAddMenuEntry("Extra Large", 4);

    int stationAngleMenu;
    stationAngleMenu = glutCreateMenu(stationMenu);
    glutAddMenuEntry("60 Degrees", 1);
    glutAddMenuEntry("120 Degrees", 2);
    glutAddMenuEntry("180 Degrees", 3);
    glutAddMenuEntry("240 Degrees", 4);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("Moon Size", moonMenu);
    glutAddSubMenu("Rotate Station", stationMenu);
    glutAddMenuEntry("Rotate Sky", 1);

    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Mouse callback routine for Control Panel.
void MouseControlPanel(int button, int state, int x, int y)
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
                spaceStation = false;
            }
            else {
                firstBoxChecked = true;
                spaceStation = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 55 && yMouse <= 60)
        {
            if (secondBoxChecked)
            {
                secondBoxChecked = false;
                alienShip = false;
            }
            else {
                secondBoxChecked = true;
                alienShip = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 45 && yMouse <= 50)
        {
            if (thirdBoxChecked)
            {
                thirdBoxChecked = false;
                jupiter = false;
            }
            else {
                thirdBoxChecked = true;
                jupiter = true;
            }
        }
        if (xMouse >= 25 && xMouse <= 30 && yMouse >= 35 && yMouse <= 40)
        {
            if (fourthBoxChecked)
            {
                fourthBoxChecked = false;
                ursaMajor = false;
            }
            else {
                fourthBoxChecked = true;
                ursaMajor = true;
            }
        }

        // Radio buttons controller
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 65 && yMouse <= 70) {
            radiobuttonselected = 1;
            moonAngle = 90;
        }
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 55 && yMouse <= 60) {
            radiobuttonselected = 2;
            moonAngle = 30;
        } 
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 45 && yMouse <= 50) {
            radiobuttonselected = 3;
            moonAngle = 0;
        } 
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 35 && yMouse <= 40) {
            radiobuttonselected = 4;
            moonAngle = -30;
        } 
        if (xMouse >= 60 && xMouse <= 65 && yMouse >= 25 && yMouse <= 30) {
            radiobuttonselected = 5;
            moonAngle = -90;
        } 

        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
    }
}

// Mouse callback routine for Sky Panel.
void MouseSkyPanel(int button, int state, int x, int y)
{
    //int xMouse, yMouse;
    /*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
    }*/
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


// Drawing routine for Control Panel.
void drawSceneControlPanel(void)
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

// Drawing routine for Sky Panel.
void drawSceneSkyPanel(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 50.0);

    glPushMatrix();
    glTranslated(0.0, 0.0, -10);
    glScaled(moonSize, moonSize, 1);
    drawMoon();
    glPopMatrix();
    
   
    drawStars();

    if (spaceStation) {
        glPushMatrix();
        glRotated(stationAngle, 0, 0, 1);
        glTranslated(-4.5, 4.5, 0.0);
        drawSpaceStation();
        glPopMatrix();
    }

    if (jupiter) {
        drawJupiter();
    }

    if (ursaMajor) {
        glPushMatrix();
        glScaled(1.4, 1.4, 1.0);
        glTranslated(0.0, 5.0, 0.0);
        drawUrsaMajor();
        glPopMatrix;
    }

    glutSwapBuffers(); //instead of glFlush, double buffer
}

// Setup for Control Panel
void setupControlPanel(void) 
{
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  
}

// Setup for Sky Panel
void setupSkyPanel(void)
{
    glClearColor(0.0078431372549019607843137254902, 0.066666, 0.11764705882352941176470588235294, 1.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    
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
        moonAngle = 90;
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
        break;

    case 'c':
        radiobuttonselected = 2;
        moonAngle = 30;
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
        break;

    case 'h':
        radiobuttonselected = 3;
        moonAngle = 0;
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
        break;

    case 'g':
        radiobuttonselected = 4;
        moonAngle = -30;
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
        glutPostRedisplay();
        break;

    case 'f':
        radiobuttonselected = 5;
        moonAngle = -90;
        glutSetWindow(controlPanel);
        glutPostRedisplay();
        glutSetWindow(skyPanel);
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
  
  // Control Panel
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(100, 100);
  controlPanel = glutCreateWindow("Control Panel");
  setupControlPanel();
  glutDisplayFunc(drawSceneControlPanel);
  glutMouseFunc(MouseControlPanel);

  // Sky Panel
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(900, 100);
  skyPanel = glutCreateWindow("Sky");
  setupSkyPanel();
  glutDisplayFunc(drawSceneSkyPanel);
  glutMouseFunc(MouseSkyPanel);

  // Both Panels
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  
  glutMainLoop(); 
  
  return 0;  
}

