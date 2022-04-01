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
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslated(0, 14, -49);
    glScaled(40, 70, .25);
    glutSolidCube(1);
    glPopMatrix();

    //First Half of Close Wall
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
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(rightDoorXPos, 9, rightDoorZPos);
    glRotated(rightDoorAngle, 0, 1, 0);
    glScaled(9.5, 30, .75);
    glutSolidCube(1);
    glPopMatrix();

    //Right door details
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
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(14.5, 9, 19);
    glScaled(1, 2, .15);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTable()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(18, 3, -47);
    glScaled(8, .5, 15);
    glutSolidCube(1);
    glPopMatrix();

    //Front left leg
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
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-7, 3, -47);
    glScaled(15, .5, 5);
    glutSolidCube(1);
    glPopMatrix();

    //Front right leg
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

void drawLights()
{
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, -15);
    glScaled(1, 1, 1);
    glutWireSphere(3, 25, 25);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, 0);
    glScaled(1, 1, 1);
    glutWireSphere(3, 25, 25);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(0, 25, -30);
    glScaled(1, 1, 1);
    glutWireSphere(3, 25, 25);
    glPopMatrix();
}

void drawPillers()
{
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(11, 5, 22);
    glScaled(2, 10, 2);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(11, 12, 22);
    glScaled(1, 1, 1);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-11, 5, 22);
    glScaled(2, 10, 2);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-11, 12, 22);
    glScaled(1, 1, 1);
    glutSolidSphere(2, 25, 25);
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
    glEnable(GL_DEPTH_TEST);

    //View
    gluLookAt(fpX, 5, fpZ,
        fpX + sin(degrees * PI/180), 5, fpZ + cos(degrees * PI / 180),
        0, 1, 0);
    

    if (selecting) {
        drawItems();
        getID(xMouse, yMouse);
    }
    else {
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

//void moveBackward() {
//    float newFpZ = fpZ - stepsize * sin(degrees * PI / 180);
//    float newFpX = fpX - stepsize * sin(degrees * PI / 180);
//    if (newFpZ != leftDoorZPos && newFpX != leftDoorXPos && newFpZ < 29)
//    {
//        fpX -= stepsize * sin(degrees * PI / 180);
//        fpZ -= stepsize * cos(degrees * PI / 180);
//    }
//}

//void moveForward() {
//    float newFpZ = fpZ + stepsize * sin(degrees * PI / 180);
//    float newFpX = fpX + stepsize * sin(degrees * PI / 180);
//    if (newFpZ != leftDoorZPos && newFpX != leftDoorXPos)
//    {
//        fpX += stepsize * sin(degrees * PI / 180);
//        fpZ += stepsize * cos(degrees * PI / 180);
//    }
//}

void keyInputSpecial(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_DOWN:
        fpX -= stepsize * sin(degrees * PI / 180);
        fpZ -= stepsize * cos(degrees * PI / 180);
        cout << "First Person Z-Coordinate: " << fpZ << endl;
        cout << "Left Door Z-Coordinate: " << leftDoorZPos << endl;
        cout << "Left Door X-Coordinate: " << leftDoorXPos << endl;
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:
        fpX += stepsize * sin(degrees * PI / 180);
        fpZ += stepsize * cos(degrees * PI / 180);
        cout << "First Person Z-Coordinate: " << fpZ << endl;
        cout << "Left Door Z-Coordinate: " << leftDoorZPos << endl;
        cout << "Left Door X-Coordinate: " << leftDoorXPos << endl;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        degrees -= rotsize;
        cout << "Degrees: " << degrees << endl;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        degrees += rotsize;
        cout << "Degrees: " << degrees << endl;
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

