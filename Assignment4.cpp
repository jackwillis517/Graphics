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
* References:
* I used the following website to figure out the name of the freezing spell in Harry Potter
* https://www.frankslide.com/what-harry-potter-spell-freezes-things/
*
* Interactions:
* Press d to open/close doors
* Press L to turn on/off lights
* Press s to teleport the flashlight in front of you and turn it on
* Press f to turn on/off the flashlight
* Press w to select the wand and start the house guessing
* Press e to translate right
* Press q to translate left
* Press G to select house Gryffindor
* Press H to select house Hufflepuff
* Press R to select house Ravenclaw
* Press S to select house Slytherin
* Press > to increase ambient lighting
* Press < to decrease ambient lighting
* Press Up Arrow to move forward
* Press Down Arrow to move backward
* Press Left Arrow to rotate left
* Press Right Arrow to rotate right
*******************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <random>
#include <ctime>
#include<cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define ONE_BY_ROOT_THREE 0.57735

//Other globals
using namespace std;
static int PI = 3.14159;
static int randNum;
static int selectedNum;
static bool red = false;
static bool blue = false;
static bool purple = false;
static bool green = false;
static float snitchX = -10;
static float snitchY = 4;
static float snitchZ = -46;
static bool giveSnitch = false;

//Color picking globals
static int DOOR = 1;
static int LIGHTS = 2;
static int WAND = 3;
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
static bool selecting = false;

//Light globals
static bool lightsOn = false;
static bool spotlightOn = false;
static bool flashlightFollow = false;
static int lightsClicked = 0;
static float globAmbVal = 0.0;
static float flashLightX = 16;
static float flashLightY = 3.5;
static float flashLightZ = -44;

//Animation globals
static bool hatAnimate = false;
static bool wandAnimate = false;
static bool doorOpen = false;
static bool spiderAnimate = false;
static bool freezeSpider = false;
static float hatRot = 0.0;
static float hatHeight = 0.0;
static float wandAnimateX = 0.0;
static float wandAnimateY = 0.0;
static float wandAnimateZ = 0.0;
static float spiderZ = -10;
static int act = 1;

//First person movement globals
static float fpX = 0.0;
static float fpY = 5.0;
static float fpZ = 28.0;
static float stepsize = 1;
static float rotsize = 5;
static float degrees = 188;
static bool canMove = true;

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

//Lighting globals
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
//Dark Purple
float matAmbAndDifDarkPurple[] = { 0.9, 0.2, 0.9, 1.0 };
//Dark Gray
float matAmbAndDifDarkGrey[] = { 0.1, 0.1, 0.1, 1.0 };
//Gray
float matAmbAndDifGrey[] = { 0.4, 0.4, 0.4, 1.0 };
//Yellow
float matAmbAndDifYellow[] = { 0.9, 0.9, 0.0, 1.0 };
//Brown
float matAmbAndDifBrown[] = { 0.2, 0.1, 0.1, 1.0 };
//Material globals
float noEmiss[] = { 0.0, 0.0, 0.0, 1.0 };
float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float matSpecBlue[] = { 0.0, 0.0, 1.0, 1.0 };
float matShine[] = { 50.0 };
float noShine[] = { 128.0 };
float lotsShine[] = { 3.0 };



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
    else if ((int)pixel[0] == 255 && (int)pixel[1] == 255 && (int)pixel[2] == 255) {
        itemID = LIGHTS;
        lightsClicked++;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255) {
        itemID = WAND;
    }
    else itemID = 0;
    

    selecting = false;
    glutPostRedisplay();
}

//Bitmap function for writing text to the screen
void writeStrokeString(void* font, char* string)
{
    char* c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

//Collision function for checking for animation collisions
void checkCollision() {
    if (fpX >= 11 && fpX <= 13 && fpZ <= -40 && fpZ >= -48) {
        flashlightFollow = true;
        glEnable(GL_LIGHT2);
    }
    glutPostRedisplay();
}

//Checks the house guess
void decider()
{
    if (randNum == selectedNum && randNum == 0) {
        act = 0;
        red = true;
        giveSnitch = true;
        cout << "Your intuition has served you well student." << endl;
        cout << "5 points to Gryffindor!" << endl;
        cout << "A snitch has been given to you." << endl;
        glutPostRedisplay();
    }
    else if (randNum == selectedNum && randNum == 1) {
        act = 0;
        blue = true;
        giveSnitch = true;
        cout << "Your intuition has served you well student." << endl;
        cout << "5 points to Hufflepuff!" << endl;
        cout << "A snitch has been given to you." << endl;
        glutPostRedisplay();
    }
    else if (randNum == selectedNum && randNum == 2) {
        act = 0;
        purple = true;
        giveSnitch = true;
        cout << "Your intuition has served you well student." << endl;
        cout << "5 points to Ravenclaw!" << endl;
        cout << "A snitch has been given to you." << endl;
        glutPostRedisplay();
    }
    else if (randNum == selectedNum && randNum == 3) {
        act = 0;
        green = true;
        giveSnitch = true;
        cout << "Your intuition has served you well student." << endl;
        cout << "5 points to Slytherin!" << endl;
        cout << "A snitch has been given to you." << endl;
        glutPostRedisplay();
    }
    else
    {
        canMove = false;
        fpZ = -43.9975;
        fpX = 0.594656;
        fpY = -14;
        globAmbVal = -0.6;
        glDisable(GL_LIGHT1);
        act = 0;
        spiderAnimate = true;
        cout << "Your intuition has failed you student, TO AZKABAN WITH YOU!!!" << endl;
        cout << "A sense of dread washes over you..." << endl;
        cout << "You are not alone." << endl;
        cout << "Rotate to confront the beast!" << endl;
        // This is where I used the URL reference above //
        cout << "Quick cast Petrificus Totalus (p) to stop the arachnid!" << endl;
    }
}
//--------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Animations-------------------------------------------------------//
void animateSpider()
{
    if (spiderZ > -25) {
        spiderZ -= .00006;
    }
}

void spiderAnimation(int x)
{
    if (!freezeSpider)
    {
        if (spiderAnimate) animateSpider();
        glutTimerFunc(100, spiderAnimation, 1);
    }
    
}

void animateWand()
{
    if (act == 1) {
        if (wandAnimateY < 5) {
            wandAnimateY += .005;
        }
        else {
            act = 2;
        }
    }

    if (act == 2) {
        if (wandAnimateX > -5) {
            wandAnimateX -= .0005;
        }
        else {
            act = 3;
        }
    }

    if (act == 3) {
        if (wandAnimateX < 0) {
            wandAnimateX += .0005;
        }
        else {
            act = 2;
        }
    }
}

void wandAnimation(int x)
{
    if (wandAnimate) animateWand();
    glutTimerFunc(100, wandAnimation, 1);
}

void animateHat()
{
    if (hatRot < 180) {
        hatRot += .05;
        hatHeight += .0010;
    }
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
    //Roof
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(-19.5, 24, -50);
        glVertex3f(19.5, 24, -50);
        glVertex3f(19.5, 24, 20);
        glVertex3f(-19.5, 24, 20);
    glEnd();

    //Floor
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(-19.5, 0.0, -50);
        glVertex3f(19.5, 0.0, -50);
        glVertex3f(19.5, 0.0, 20);
        glVertex3f(-19.5, 0.0, 20);
    glEnd();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(-19.5, 0.0, 20);
        glVertex3f(19.5, 0.0, 20);
        glVertex3f(19.5, 0.0, 40);
        glVertex3f(-19.5, 0.0, 40);
    glEnd();

    //Left Wall
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glShadeModel(GL_FLAT);
    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-19.5, 24, -50);
        glVertex3f(-19.5, 24, 20);
        glVertex3f(-19.5, -1.0, 20);
        glVertex3f(-19.5, -1.0, -50);
    glEnd();
    glShadeModel(GL_SMOOTH);

    //Right Wall
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(19.5, 24, -50);
        glVertex3f(19.5, 24, 20);
        glVertex3f(19.5, -1.0, 20);
        glVertex3f(19.5, -1.0, -50);
    glEnd();

    //Back Wall
    glPushMatrix();
    glTranslated(-20.0, 0.0, -50.0);
    glScaled(40.0, 25.0, 25.0);
    double n = 100.0;
    glNormal3f(0.0, 0.0, 1.0);
    for (int r = 0; r < n; r++)
    {
        if (r % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= n; c++)
        {
            glVertex3f(c / n, r / n, 0.0);
            glVertex3f(c / n, (r + 1) / n, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    //First Half of Close Wall
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-19.5, 24, 20);
        glVertex3f(-9.0, 24, 20);
        glVertex3f(-9.0, -1.0, 20);
        glVertex3f(-19.5, -1.0, 20);
    glEnd();

    //Second Half of Close Wall
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glBegin(GL_POLYGON);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(19.5, 24, 20);
        glVertex3f(9.0, 24, 20);
        glVertex3f(9.0, -1.0, 20);
        glVertex3f(19.5, -1.0, 20);
    glEnd();
}

void drawDungeon() 
{
    //Floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-19.5, -20.0, -50);
    glVertex3f(19.5, -20.0, -50);
    glVertex3f(19.5, -20.0, 20);
    glVertex3f(-19.5, -20.0, 20);
    glEnd();

    //Ceiling
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-19.5, -3.0, -50);
    glVertex3f(19.5, -3.0, -50);
    glVertex3f(19.5, -3.0, 20);
    glVertex3f(-19.5, -3.0, 20);
    glEnd();

    //Left Wall
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-19.5, -1.0, -50);
    glVertex3f(-19.5, -1.0, 20);
    glVertex3f(-19.5, -20.0, 20);
    glVertex3f(-19.5, -20.0, -50);
    glEnd();

    //Right Wall
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(19.5, -1.0, -50);
    glVertex3f(19.5, -1.0, 20);
    glVertex3f(19.5, -20.0, 20);
    glVertex3f(19.5, -20.0, -50);
    glEnd();

    //Back Wall
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-19.5, -1.0, -50);
    glVertex3f(19.5, -1.0, -50);
    glVertex3f(19.5, -20.0, -50);
    glVertex3f(-19.5, -20.0, -50);
    glEnd();

    //Front Wall
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-19.5, -1.0, 18);
    glVertex3f(19.5, -1.0, 18);
    glVertex3f(19.5, -20.0, 18);
    glVertex3f(-19.5, -20.0, 18);
    glEnd();
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noShine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecBlue);
    glPushMatrix();
    glTranslated(-7, 3.5, -47);
    glRotated(90, 1, 0, 0);
    glScaled(1, 1, 1);
    glutSolidTorus(.25, 1.5, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-7, 3.5, -47);
    glRotated(-90, 1, 0, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1.5, 4, 20, 20);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lotsShine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glPushMatrix();
    glTranslated(-7, 7.5, -47);
    glutSolidSphere(.3, 25, 25);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
}

void drawWand()
{
    if (wandAnimate) {
        float wandEmiss[] = { 0.0, 0.9, 0.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, wandEmiss);
    }
    else
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    }
    
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(-3, 3.5, -46);
    glScaled(.15, .15, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmiss);
}

void drawFlashlight()
{
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
        glColor3f(0.0, 1.0, 0.0);
        glPushMatrix();
        glTranslated(flashLightX, flashLightY, flashLightZ);
        glRotated(180, 0, 1, 0);
        glScaled(.35, .35, 2);
        glutSolidCube(1);
        glPopMatrix();

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslated(flashLightX, flashLightY, flashLightZ + 1);
        glScaled(.5, .5, .5);
        glutSolidCube(1);
        glPopMatrix();
}

void drawLights()
{
    if (lightsOn) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    }
    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, -15);
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
    if (freezeSpider)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifDarkGrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noShine);
    glPushMatrix();
    glTranslated(-14, 5, -10);
    glScaled(1.5, 1, 1);
    glutSolidSphere(3.5, 25, 25);
    glPopMatrix();

    //Head
    if (freezeSpider)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifBlue);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifGrey);
    }
    glPushMatrix();
    glTranslated(-8, 5, -10);
    glScaled(1.5, .7, 1.0);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();

    //Left legs
    if (freezeSpider)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifBlue);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifDarkGrey);
    }
    
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
    float eyeEmiss[] = { 0.9, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, eyeEmiss);
    glPushMatrix();
    glTranslated(-5.2, 5.2, -9.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();
    

    //Right eye
    glPushMatrix();
    glTranslated(-5.2, 5.2, -10.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmiss);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
}

void drawSpider2()
{
    //Body
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifDarkGrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noShine);
    glPushMatrix();
    glTranslated(-14, 5, -10);
    glScaled(1.5, 1, 1);
    glutSolidSphere(3.5, 25, 25);
    glPopMatrix();

    //Head
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifGrey);
    glPushMatrix();
    glTranslated(-8, 5, -10);
    glScaled(1.5, .7, 1.0);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();

    //Left legs
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmbAndDifDarkGrey);
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
    float eyeEmiss[] = { 0.9, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, eyeEmiss);
    glPushMatrix();
    glTranslated(-5.2, 5.2, -9.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();


    //Right eye
    glPushMatrix();
    glTranslated(-5.2, 5.2, -10.45);
    glutSolidSphere(.20, 25, 25);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmiss);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
}

void drawSmiley()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glPushMatrix();
    glTranslated(-15, 17, 12);
    glutSolidSphere(4, 25, 25);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(-11, 17, 11);
    glutSolidSphere(.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-11, 17, 13);
    glutSolidSphere(.5, 25, 25);
    glPopMatrix();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-11, 15, 10);
        glVertex3f(-11, 13, 12);
        glVertex3f(-11, 15, 14);
        glVertex3f(-11, 14, 12);
    glEnd();
}

void drawText()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-17, 10.0, -47);
    glScalef(0.004, 0.004, 0.004);
    char text[] = "Guess a House: (G) Gryffindor, (H) Hufflepuff, (R) Ravenclaw, (S) Slytherin";
    writeStrokeString(GLUT_STROKE_ROMAN, text);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-19.5, 12.0, -48);
    glVertex3f(4.5, 12.0, -48);
    glVertex3f(4.5, 10.0, -48);
    glVertex3f(-19.5, 10.0, -48);
    glEnd();
}

void drawBroomstick()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBrown);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 12, -20);
    glScaled(10, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5, 12, -20);
    glScaled(3, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.45, -20);
    glRotated(-25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.7, -20);
    glRotated(-15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.15, -20);
    glRotated(15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.45, -20);
    glRotated(25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.45, -19.5);
    glRotated(-25, 0, 1, 0);
    glRotated(-25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.7, -19.5);
    glRotated(-25, 0, 1, 0);
    glRotated(-15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.15, -19.5);
    glRotated(-25, 0, 1, 0);
    glRotated(15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.45, -19.5);
    glRotated(-25, 0, 1, 0);
    glRotated(25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.45, -20.5);
    glRotated(25, 0, 1, 0);
    glRotated(-25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 11.7, -20.5);
    glRotated(25, 0, 1, 0);
    glRotated(-15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.15, -20.5);
    glRotated(25, 0, 1, 0);
    glRotated(15, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(5.65, 12.45, -20.5);
    glRotated(25, 0, 1, 0);
    glRotated(25, 0, 0, 1);
    glScaled(1.5, .05, .05);
    glutSolidCube(1);
    glPopMatrix();

    
}

void drawPurpleCube()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkPurple);
    glPushMatrix();
    glTranslated(8.5, .5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawRedCube()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslated(4, .5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawBlueCube()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(5.5, .5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawGreenCube()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glPushMatrix();
    glTranslated(7, .5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawPurpleCube2()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkPurple);
    glPushMatrix();
    glTranslated(8.5, 1.5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawRedCube2()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslated(4, 1.5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawBlueCube2()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(5.5, 1.5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawGreenCube2()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glPushMatrix();
    glTranslated(7, 1.5, -48);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSnitch()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lotsShine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glPushMatrix();
    glTranslated(snitchX, snitchY, snitchZ);
    glutSolidSphere(.2, 25, 25);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
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
    
    glPushMatrix();
    glTranslated(-7, 4, -47);
    glTranslated(0.0, hatHeight, 0.0);
    glRotated(hatRot, 1, 0, 0);
    glTranslated(7, -4, 47);
    drawHat();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3, 3.5, -46);
    glTranslated(wandAnimateX, wandAnimateY, wandAnimateZ);
    glTranslated(3, -3.5, 46);
    drawWand();
    glPopMatrix();

    drawLights();

    glPushMatrix();
    glRotated(-10, 0, 1, 0);
    drawSpider();
    glPopMatrix();

    glPushMatrix();
    glScaled(2.0, 2.0, 2.0);
    glTranslated(10.0, -10.0, spiderZ);
    glRotated(90, 0, 1, 0);
    drawSpider();
    glPopMatrix();

    drawSmiley();
    drawDungeon();

    glPushMatrix();
    glTranslated(-5.0, 0.0, -10.0);
    glRotated(-90, 0, 1, 0);
    drawBroomstick();
    glPopMatrix();

    drawRedCube();
    drawBlueCube(); 
    drawPurpleCube();
    drawGreenCube();

    if (red) drawRedCube2();
    if (blue) drawBlueCube2();
    if (purple) drawPurpleCube2();
    if (green) drawGreenCube2();


    if (itemID == DOOR && doorClicked == 1) {
        doorOpen = true;
    }
    if (itemID == DOOR && doorClicked == 2) {
        doorClicked = 0;
        doorOpen = false;
    }
    if (itemID == LIGHTS && lightsClicked == 1) {
        lightsOn = true;
        glEnable(GL_LIGHT1);
    }
    if (itemID == LIGHTS && lightsClicked == 2) {
        lightsClicked = 0;
        lightsOn = false;
        glDisable(GL_LIGHT1);
    }
    if (itemID == WAND) {
        wandAnimate = true;
        hatAnimate = true;
        drawText();
    }

    doorAnimation(1);
    hatAnimation(1);
    wandAnimation(1);
    spiderAnimation(1);

    checkCollision();
    if (flashlightFollow) {
        float lightPos2[] = { flashLightX, flashLightY, flashLightZ, 1.0 };
        float spotDirection[] = { 0.0, 0.0, 1.0 };
        glPushMatrix();
        glTranslated(fpX, fpY, fpZ);
        glRotated(degrees, 0, 1, 0);
        glTranslated(-fpX, -fpY, -fpZ);
        glTranslated(fpX - flashLightX + 2, fpY - flashLightY - 1, fpZ - flashLightZ + 2);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
        drawFlashlight();
        glPopMatrix();
    }
    else {
        drawFlashlight();
    }

    if (giveSnitch)
    {
        glPushMatrix();
        glTranslated(fpX, fpY, fpZ);
        glRotated(degrees, 0, 1, 0);
        glTranslated(-fpX, -fpY, -fpZ);
        glTranslated(fpX - snitchX + 2, fpY - snitchY + 2, fpZ - snitchZ + 2);
        drawSnitch();
        glPopMatrix();
    }
    else {
        drawSnitch();
    }
}


//Drawing to Screen Function
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Global light
    float globAmb[] = { globAmbVal, globAmbVal, globAmbVal, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    //Light2 - Flashlight spotlight
    float spotAngle = 25;
    float spotExponent = 1.0;
    float lightAmb2[] = { 0.9, 0.0, 0.0, 1.0 };
    float lightDifAndSpec2[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpec2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpec2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);

    //View
    gluLookAt(fpX, fpY, fpZ,
        fpX + sin(degrees * PI/180), fpY, fpZ + cos(degrees * PI / 180),
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

//Setup Screen Function
void setup(void)
{
    glClearColor(0.1843137254901960784313725490196, 0.16862745098039215686274509803922, 0.18823529411764705882352941176471, 0.0);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));
    randNum = rand() % 4;
    cout << "*============================================================*" << endl;
    cout << "*==========================Cheat Code========================*" << endl;
    cout << "*Random Number is: " << randNum << "                                         *" << endl;
    cout << "*Gryffindor: 0 | Hufflepuff: 1 | Ravenclaw: 2 | Slytherin: 3 *" << endl;
    cout << "*============================================================*" << endl;
    cout << "*============================================================*" << endl;

    //Master lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    //Light0 - Main ambiant light
    float lightAmb0[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos0[] = { 0.0, 1.5, 3.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT0);

    //Light1 - Roof light
    float lightAmb1[] = { 0.3, 0.3, 0.3, 1.0 };
    float lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos1[] = { 0, 25, -15, 1.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
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

    case 'L':
        if (lightsOn) {
            lightsOn = false;
            lightsClicked = 0;
            glDisable(GL_LIGHT1);
        }
        else {
            lightsOn = true;
            lightsClicked++;
            glEnable(GL_LIGHT1);
        }
        break;

    case 's':
        spotlightOn = true;
        flashlightFollow = true;
        glEnable(GL_LIGHT2);
        break;

    case 'f':
        if (spotlightOn) {
            spotlightOn = false;
            glDisable(GL_LIGHT2);
        }
        else {
            spotlightOn = true;
            glEnable(GL_LIGHT2);
        }
        break;

    case 'w':
        itemID = WAND;
        break;

    case '>':
        globAmbVal += 0.1;
        break;

    case '<':
        globAmbVal -= 0.1;
        break;

    case 'q':
        fpX -= stepsize;
        break;

    case 'e':
        fpX += stepsize;
        break;

    case 'G':
        selectedNum = 0;
        wandAnimate = false;
        decider();
        break;

    case 'H':
        selectedNum = 1;
        wandAnimate = false;
        decider();
        break;

    case 'R':
        selectedNum = 2;
        wandAnimate = false;
        decider();
        break;

    case 'S':
        selectedNum = 3;
        wandAnimate = false;
        decider();
        break;

    case 'p':
        freezeSpider = true;
        cout << "The giant spider is frozen, you have proven yourself worthy." << endl;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void keyInputSpecial(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_DOWN:
        if (canMove) {
            fpX -= stepsize * sin(degrees * PI / 180);
            fpZ -= stepsize * cos(degrees * PI / 180);
        }
        break;

    case GLUT_KEY_UP:
        if (canMove) {
            fpX += stepsize * sin(degrees * PI / 180);
            fpZ += stepsize * cos(degrees * PI / 180);
        }
        break;

    case GLUT_KEY_RIGHT:
        degrees -= rotsize;
        break;

    case GLUT_KEY_LEFT:
        degrees += rotsize;
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
    cout << "Press d to open / close doors" << endl;
    cout << "Press L to turn on / off lights" << endl;
    cout << "Press s to teleport the flashlight in front of you and turn it on" << endl;
    cout << "Press f to turn on / off the flashlight" << endl;
    cout << "Press w to select the wand and start the house guessing" << endl;
    cout << "Press e to translate right" << endl;
    cout << "Press q to translate left" << endl;
    cout << "Press G to select house Gryffindor" << endl;
    cout << "Press H to select house Hufflepuff" << endl;
    cout << "Press R to select house Ravenclaw" << endl;
    cout << "Press S to select house Slytherin" << endl;
    cout << "Press > to increase ambient lighting" << endl;
    cout << "Press < to decrease ambient lighting" << endl;
    cout << "Press Up Arrow to move forward" << endl;
    cout << "Press Down Arrow to move backward" << endl;
    cout << "Press Left Arrow to rotate left" << endl;
    cout << "Press Right Arrow to rotate right" << endl;
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

