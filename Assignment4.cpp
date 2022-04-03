/******************************************
*
* Official Name:  Jack Andrew Willis
*
* Call me: Jack
*
* E-mail:  jwilli59@syr.edu
*
* Assignment:  Assignment 4
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  April 11, 2022
*
* References: None
*
* Interactions:
*******************************************/

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define ONE_BY_ROOT_THREE 0.57735

using namespace std;
static int PI = 3.14159;
static int DOOR = 1;
static int TORUS = 2;
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
static bool selecting = false;
static bool hatAnimate = false;

static bool wandAnimate = false;
static bool doorOpen = false;
static bool lightsOn = false;
static bool spotlightOn = false;
static bool flashlightOn = false;

//First person movement globals
static float fpX = 0;
static float fpZ = 28;
static float stepsize = 1;
static float rotsize = 5;
static float degrees = 188;

//Door globals
static float leftDoorAngle = 0;
static float leftDoorXPos = -4.5;
static float leftDoorZPos = 20;
static float leftDoorYPos = 9;
static float rightDoorAngle = 0;
static float rightDoorXPos = 4.5;
static float rightDoorZPos = 20;
static float rightDoorYPos = 9;
static int doorClicked = 0;

//Lighting
//Red
float matAmbAndDifRed[] = { 0.9, 0.0, 0.0, 1.0 };
//Green
float matAmbAndDifGreen[] = { 0.0, 0.9, 0.0, 1.0 };
//White
float matAmbAndDifWhite[] = { 0.9, 0.9, 0.9, 1.0 };
//Black
float matAmbAndDifBlack[] = { 0.0, 0.0, 0.0, 1.0 };
//Blue
float matAmbAndDifBlue[] = { 0.0, 0.0, 0.9, 1.0 };
//Orange
float matAmbAndDifOrange[] = { 0.9, 0.5, 0.0, 1.0 };
//Purple
float matAmbAndDifPurple[] = { 0.9, 0.5, 0.9, 1.0 };
//Dark Gray
float matAmbAndDifDarkGrey[] = { 0.1, 0.1, 0.1, 1.0 };
//Gray
float matAmbAndDifGrey[] = { 0.4, 0.4, 0.4, 1.0 };
//Yellow
float matAmbAndDifYellow[] = { 0.9, 0.9, 0.0, 1.0 };


float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float matShine[] = { 50.0 };



//---------------------------------------------Utility Functions------------------------------------------------//
//Projection for entire project
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

//Identification function for color picking
void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0) {
        itemID = DOOR;
        doorClicked++;
    }
    else {
        itemID = 0;
    }

    selecting = false;
    glutPostRedisplay();
}

//Bitmap function for writing text to the screen
void writeBitmapString(void* font, const char* string)
{
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}



//Collision function for checking for animation collisions
void checkCollision() {
    
    glutPostRedisplay();
}
//--------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Animations-------------------------------------------------------//
void animateHat()
{

    glutPostRedisplay();
}

void hatAnimation(int x) 
{
    if (hatAnimate) animateHat();
    glutTimerFunc(100, hatAnimation, 1);
}

void animateDoorsClosed()
{
    if (leftDoorAngle < 0) {
        leftDoorAngle += .005;
        leftDoorXPos += .00025;
        leftDoorZPos -= .00025;
    }

    if (rightDoorAngle > 0) {
        rightDoorAngle -= .005;
        rightDoorXPos -= .00025;
        rightDoorZPos -= .00025;
    }
    glutPostRedisplay();
}

void animateDoorsOpen()
{
    if (leftDoorAngle > -90) {
        leftDoorAngle -= .005;
        leftDoorXPos -= .00025;
        leftDoorZPos += .00025;
    }

    if (rightDoorAngle < 90) {
        rightDoorAngle += .005;
        rightDoorXPos += .00025;
        rightDoorZPos += .00025;
    }
    
    glutPostRedisplay();
}

void doorAnimation(int x)
{
    if (doorOpen) animateDoorsOpen();

    if (!doorOpen && leftDoorAngle < 0) animateDoorsClosed();
    glutTimerFunc(100, doorAnimation, 1);
}


//-------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Drawing Functions-----------------------------------------------//
void drawFloorAndWalls()
{
    //Floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3f(1.0, .5, 1.0);
    glPushMatrix();
    glTranslated(0, -.5, -9);
    glScaled(40, .25, 80);
    glutSolidCube(1);
    glPopMatrix();

    //Roof
    glColor3f(.5, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 24, -20);
    glScaled(40, .25, 80);
    glutSolidCube(1);
    glPopMatrix();

    //Left Wall
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(-20, 6.5, -15);
    glScaled(.25, 35, 70);
    glutSolidCube(1);
    glPopMatrix();

    //Right Wall
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(20, 6.5, -15);
    glScaled(.25, 35, 70);
    glutSolidCube(1);
    glPopMatrix();

    //Back Wall
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslated(0, 14, -49);
    glScaled(40, 70, .25);
    glutSolidCube(1);
    glPopMatrix();

    //First Half of Close Wall
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-14.5, 9, 20);
    glScaled(11, 30, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Second Half of Close Wall
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(14.5, 9, 20);
    glScaled(11, 30, .25);
    glutSolidCube(1);
    glPopMatrix();
}

void drawLeftDoor()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, leftDoorYPos, leftDoorZPos);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9.5, 30, .75);
    glutSolidCube(1);
    glPopMatrix();
}

void drawRightDoor()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 9, rightDoorZPos);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9.5, 30, .75);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    //Right and left door details
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 5, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos , 9, rightDoorZPos+.5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 13, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 17, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 21, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Right cross bars
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 5, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 9, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 14, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 12, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 17, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 21, rightDoorZPos + .5);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Left door boxes
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 5, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 9, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 13, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 17, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 21, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(3, 3, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Left cross bars
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 5, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 9, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 14, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 12, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 17, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(leftDoorXPos, 21, leftDoorZPos + .5);
    glRotated(leftDoorAngle, 0, 1, 0);
    glScaled(9, .25, .25);
    glutSolidCube(1);
    glPopMatrix();
}

void drawLightSwitch()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(14.5, 9, 19);
    glScaled(1, 2, .15);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTable()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(18, 3, -47);
    glScaled(8, .5, 15);
    glutSolidCube(1);
    glPopMatrix();

    //Front left leg
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(14.75, .5, -40);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Back left leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(14.75, .5, -48);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Front right leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(19, .5, -40);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Back right leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(19, .5, -48);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTable2() 
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-7, 3, -47);
    glScaled(15, .5, 5);
    glutSolidCube(1);
    glPopMatrix();

    //Front right leg
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, .5, -45);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Back right leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, .5, -48.5);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Front left leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-14, .5, -45);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();

    //Back left leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-14, .5, -48.5);
    glScaled(.25, 5, .25);
    glutSolidCube(1);
    glPopMatrix();
}

void drawHat()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(-7, 3.5, -47);
    glRotated(90, 1, 0, 0);
    glScaled(1, 1, 1);
    glutSolidTorus(.25, 1.5, 20, 20);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(-7, 3, -47);
    glRotated(-90, 1, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1.5, 4, 20, 20);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glPushMatrix();
    glTranslated(-7, 7, -47);
    glutSolidSphere(.3, 25, 25);
    glPopMatrix();
}

void drawWand()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glPushMatrix();
    glTranslated(-3, 3.5, -46);
    glScaled(.15, .15, 1.5);
    glutSolidCube(1);
    glPopMatrix();
}

void drawFlashlight()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(16, 3.5, -44);
    glRotated(90, 0, 1, 0);
    glScaled(.35, .35, 2);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(15, 3.5, -44);
    glScaled(.5, .5, .5);
    glutSolidCube(1);
    glPopMatrix();
}

void drawLights()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, -15);
    glScaled(1, 1, 1);
    glutSolidSphere(3, 25, 25);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, 0);
    glScaled(1, 1, 1);
    glutSolidSphere(3, 25, 25);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, -30);
    glScaled(1, 1, 1);
    glutSolidSphere(3, 25, 25);
    glPopMatrix();
}

void drawPillers()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(11, 5, 22);
    glScaled(2, 10, 2);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(11, 12, 22);
    glScaled(1, 1, 1);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-11, 5, 22);
    glScaled(2, 10, 2);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-11, 12, 22);
    glScaled(1, 1, 1);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();
}

void drawSpiderLegs1()
{
    //Leg1 - Part 1
    glPushMatrix();
    glTranslated(-16, 6, -6);
    glRotated(-20, 0, 1, 0);
    glRotated(-35, 1, 0, 0);
    glScaled(.35, .35, 4);
    glutSolidCube(1);
    glPopMatrix();

    //Leg1 - Part 2
    glPushMatrix();
    glTranslated(-16.5, 6.75, -3.25);
    glRotated(15, 1, 0, 0);
    glScaled(.35, .35, 2.5);
    glutSolidCube(1);
    glPopMatrix();

    //Leg1 - Part 3
    glPushMatrix();
    glTranslated(-17, 3.0, -1.0);
    glRotated(-15, 0, 1, 0);
    glRotated(70, 1, 0, 0);
    glScaled(.35, .35, 8);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSpiderLegs2()
{
    //Leg2 - Part 1
    glPushMatrix();
    glTranslated(-14, 6, -6);
    glRotated(-25, 1, 0, 0);
    glScaled(.35, .35, 4);
    glutSolidCube(1);
    glPopMatrix();

    //Leg2 - Part 2
    glPushMatrix();
    glTranslated(-14, 6.25, -3.25);
    glRotated(25, 1, 0, 0);
    glScaled(.35, .35, 2.5);
    glutSolidCube(1);
    glPopMatrix();

    //Leg2 - Part 3
    glPushMatrix();
    glTranslated(-14, 1.8, -1.4);
    glRotated(80, 1, 0, 0);
    glScaled(.35, .35, 8);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSpiderLegs3()
{
    //Leg3 - Part 1
    glPushMatrix();
    glTranslated(-12, 5, -6);
    glRotated(-10, 1, 0, 0);
    glScaled(.35, .35, 4);
    glutSolidCube(1);
    glPopMatrix();

    //Leg3 - Part 2
    glPushMatrix();
    glTranslated(-12, 5, -3);
    glRotated(20, 1, 0, 0);
    glScaled(.35, .35, 2.5);
    glutSolidCube(1);
    glPopMatrix();

    //Leg3 - Part 3
    glPushMatrix();
    glTranslated(-12, 1.4, -1.4);
    glRotated(85, 1, 0, 0);
    glScaled(.35, .35, 7);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSpiderLegs4()
{
    //Leg4 - Part 1
    glPushMatrix();
    glTranslated(-10, 5, -7);
    glRotated(15, 0, 1, 0);
    glRotated(5, 1, 0, 0);
    glScaled(.35, .35, 4);
    glutSolidCube(1);
    glPopMatrix();

    //Leg4 - Part 2
    glPushMatrix();
    glTranslated(-9.25, 4.25, -4);
    glRotated(15, 0, 1, 0);
    glRotated(25, 1, 0, 0);
    glScaled(.35, .35, 2.5);
    glutSolidCube(1);
    glPopMatrix();

    //Leg4 - Part 3
    glPushMatrix();
    glTranslated(-8.75, 0.6, -2.2);
    glRotated(15, 0, 1, 0);
    glRotated(75, 1, 0, 0);
    glScaled(.35, .35, 7);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSpider()
{
    //Body
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glPushMatrix();
    glTranslated(-14, 5, -10);
    glScaled(1.5, 1, 1);
    glutSolidSphere(3.5, 25, 25);
    glPopMatrix();

    //Head
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
    glPushMatrix();
    glTranslated(-8, 5, -10);
    glScaled(1.5, .7, 1.0);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();

    //Left legs
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    drawSpiderLegs1();
    drawSpiderLegs2();
    drawSpiderLegs3();
    drawSpiderLegs4();

    //Right legs
    glPushMatrix();
    glTranslated(-32, 0, -20);
    glRotated(-180, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    drawSpiderLegs1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-28, 0, -20);
    glRotated(-180, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    drawSpiderLegs2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-24, 0, -20);
    glRotated(-180, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    drawSpiderLegs3();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-20, 0, -20);
    glRotated(-180, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    drawSpiderLegs4();
    glPopMatrix();

    //Left eye
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslated(-5.2, 5.2, -9.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();

    //Right eye
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslated(-5.2, 5.2, -10.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();
}

void drawItems()
{
    drawFloorAndWalls();
    drawLeftDoor();
    drawRightDoor();
    drawLightSwitch();
    drawPillers();
    drawTable();
    drawTable2();
    drawHat();
    drawWand();
    drawFlashlight();

    glPushMatrix();
    glRotated(-10, 0, 1, 0);
    drawSpider();
    glPopMatrix();
    

    drawLights();
    if (itemID == DOOR && doorClicked == 1) {
        doorOpen = true;
    }

    if (itemID == DOOR && doorClicked == 2) {
        doorClicked = 0;
        doorOpen = false;
    }
    doorAnimation(1);
}

//Drawing to Screen Function
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    //View
    gluLookAt(fpX, 5, fpZ,
        fpX + sin(degrees * PI/180), 5, fpZ + cos(degrees * PI / 180),
        0, 1, 0);
    

    if (selecting) {
        glDisable(GL_LIGHTING);
        drawItems();
        getID(xMouse, yMouse);
    }
    else {
        glEnable(GL_LIGHTING);
        drawItems();
        glutSwapBuffers();
    }
}


//-------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Setup Functions-------------------------------------------------//
static float normals[] =
{
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE,
    -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE, -ONE_BY_ROOT_THREE
};

//Setup Screen Function
void setup(void)
{
    glClearColor(0.1843137254901960784313725490196, 0.16862745098039215686274509803922, 0.18823529411764705882352941176471, 0.0);
    glEnable(GL_DEPTH_TEST);

    //Master lighting
    glEnable(GL_LIGHTING);

    glEnable(GL_NORMALIZE);

    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos[] = { 0.0, 1.5, 3.0, 1.0 };
    float globAmb[] = { 0.0, 0.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals);
}

//Resize Screen Function
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    setProjection();
    height = h;
    width = w;
}

//Keyboard Input Function
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'd':
        doorOpen = !doorOpen;
        break;

    case 'l':
        lightsOn = !lightsOn;
        break;

    case 's':
        spotlightOn = !spotlightOn;
        break;

    case 'f':
        flashlightOn = !flashlightOn;
        break;

    case 'w':
        wandAnimate = !wandAnimate;
        break;

    default:
        break;
    }
}

void keyInputSpecial(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_DOWN:
        fpX -= stepsize * sin(degrees * PI / 180);
        fpZ -= stepsize * cos(degrees * PI / 180);
        cout << "First Person Z-Coordinate: " << fpZ << endl;
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:
        fpX += stepsize * sin(degrees * PI / 180);
        fpZ += stepsize * cos(degrees * PI / 180);
        cout << "First Person Z-Coordinate: " << fpZ << endl;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        degrees -= rotsize;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        degrees += rotsize;
        glutPostRedisplay();
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void mouseInput(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT) {
        selecting = true;
        xMouse = x;
        yMouse = height - y;
        glutPostRedisplay();
    }
}

//Print Intructions Function
void printInteraction(void)
{
    cout << "Interaction:" << endl;
}

//Main Loop
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Harry Potter Picking Hat");
    setup();
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(keyInputSpecial);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseInput);
    printInteraction();
    glutMainLoop();

    return 0;
}
//-------------------------------------------------------------------------------------------------------------//

