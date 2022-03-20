/******************************************
*
* Official Name:  Jack Andrew Willis
*
* Call me: Jack
*
* E-mail:  jwilli59@syr.edu
*
* Assignment:  Assignment 3
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  March 23, 2022
*
* References:  None
*
* Interactions:   
*******************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


using namespace std;
static int PI = 3.14159;

//Color picking, mouse & perspective globals
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
static bool selecting = false;
static int lookPos = 0;

//Helicopter globals
static int HELI = 1;
static int propRot = 0;
static int act = 1;
static float heliSpeed = .0003;
static float rotHeli = 0;
static bool heliPower = false;
static bool heliAnimate = false;

//Balloon globals
static bool balloonAnimate = false;

//Position globals for helicopter and balloons
static float xPosHeli = 0;
static float yPosHeli = 0;
static float zPosHeli = 0;
static float xPosBalloon1 = 6;
static float yPosBalloon1 = 1;
static float zPosBalloon1 = -6;

//Color rgbs for objects changed by balloon
static float cone1ColorR = 0.0;
static float cone1ColorG = 1.0;
static float cone1ColorB = 0.0;
static float cone2ColorR = 0.76862745098039215686274509803922;
static float cone2ColorG = 0.21568627450980392156862745098039;
static float cone2ColorB = 0.86666666666666666666666666666667;
static float cone3ColorR = 0.0;
static float cone3ColorG = 1.0;
static float cone3ColorB = 1.0;
static float torusColorR = 0.98823529411764705882352941176471;
static float torusColorG = 0.01960784313725490196078431372549;
static float torusColorB = 0.63137254901960784313725490196078;


//---------------------------------------------Utility Functions------------------------------------------------//
//Projection for entire project
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-4, 4, -4, 4, 1, 21);
    glMatrixMode(GL_MODELVIEW);
}

//Identification function for color picking
void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0) {
        itemID = HELI;
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

//Collision function for checking if the balloon hits a specific spot
void checkCollision() {
    if (xPosHeli >= -8 && xPosHeli <= -2 && zPosHeli >= -4 && zPosHeli <= 5 && yPosBalloon1 < -5) {
        cone1ColorR = 0.0;
        cone1ColorG = 0.0;
        cone1ColorB = 1.0;
        cone2ColorR = 0.0;
        cone2ColorG = 0.0;
        cone2ColorB = 1.0;
        cone3ColorR = 0.0;
        cone3ColorG = 0.0;
        cone3ColorB = 1.0;
    }
    if (xPosHeli >= -8 && xPosHeli <= -2 && zPosHeli >= -4 && zPosHeli <= -3 && yPosBalloon1 < 5) {
        torusColorR = 0.0;
        torusColorG = 0.0;
        torusColorB = 1.0;
    }
    glutPostRedisplay();
}
//--------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Animations-------------------------------------------------------//
//Animation using idle function for prop
void animateProp()
{
    if (propRot == 360) {
        propRot = 0;
    }
    
    else {
        propRot += 12;
    }
    glutPostRedisplay();
}

void propAnimation()
{
    if (heliPower) {
        glutIdleFunc(animateProp);
    }
    else {
        glutIdleFunc(NULL);
    }
}

//Animation using timer function for movement
void animateHeli(void)
{
    if (act == 1 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        else {
            act = 2;
        }
    }

    if (act == 2 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        } 
    }
    if (act == 2 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (zPosHeli < 4) {
            zPosHeli += heliSpeed;
        }
        else {
            act = 3;
        }
    }
    
    if (act == 3 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 3 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (xPosHeli > -7) {
            xPosHeli -= heliSpeed;
        }
        else {
            act = 4;
        }
    }

    if (act == 4 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 4 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (yPosHeli < 15) {
            yPosHeli += heliSpeed;
        }
        else {
            act = 5;
        }
    }
    
    if (act == 5 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 5 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (zPosHeli > -10) {
            zPosHeli -= heliSpeed;
        }
        else {
            act = 6;
        }
    }
    
    if (act == 6 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 6 && heliPower == true) {
        if (yPosHeli > 10) {
            yPosHeli -= heliSpeed;
        }
        else {
            act = 7;
        }
    }

    if (act == 7 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 7 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (xPosHeli < 10) {
            xPosHeli += heliSpeed;
        }
        else {
            act = 8;
        }
    }
    
    if (act == 8 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 8 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (zPosHeli < 5) {
            zPosHeli += heliSpeed;
        }
        else {
            act = 9;
        }
    }

    if (act == 9 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 9 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (xPosHeli > 0) {
            xPosHeli -= heliSpeed;
        }
        else {
            act = 10;
        }
    }

    if (act == 10 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 10 && heliPower == true) {
        if (yPosHeli < 10) {
            yPosHeli += heliSpeed;
        }
        if (zPosHeli > 0) {
            zPosHeli -= heliSpeed;
        }
        else {
            act = 11;
        }
    }
    
    if (act == 11 && heliPower == false) {
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
    }
    if (act == 11 && heliPower == true) { 
        if (yPosHeli > 0) {
            yPosHeli -= heliSpeed;
        }
        else {
            act = 12;
        }
    }

    if (act == 12) {
        heliAnimate = !heliAnimate;
        act = 1;
    }
    glutPostRedisplay();
}

void heliAnimation(int x)
{
    if (heliAnimate) animateHeli();

    glutTimerFunc(100, heliAnimation, 1);
}

void animateBalloon()
{
    if (yPosBalloon1 > -16) {
        yPosBalloon1 -= .005;
    }

    glutPostRedisplay();
}

void balloonAnimation(int x) 
{
    if (balloonAnimate) animateBalloon();
    glutTimerFunc(100, balloonAnimation, 1);
}
//-------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Drawing Functions-----------------------------------------------//
void drawBalloons()
{
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(xPosBalloon1, yPosBalloon1, zPosBalloon1);
    glScaled(.5, .5, .5);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
}

void drawHeli(float c1, float c2, float c3)
{
    //Helicopter Body
    glColor3f(c1, c2, c3);
    glPushMatrix();
    glTranslated(6, 3, -6);
    glScaled(2, 2, 3);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    drawBalloons();

    //Helicopter Tail
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(6, 3, -12);
    glScaled(.5, .5, 10);
    glutSolidCube(1);
    glPopMatrix();

    //Helicopter Prop
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(6, 5, -6);
    glRotated(propRot, 0, 1, 0);
    glScaled(.25, .25, 10);
    glutSolidCube(1);
    glPopMatrix();

    //Helicopter Tail Props
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(6.25, 3, -17);
    glRotated(propRot, 1, 0, 0);
    glRotated(90, 0, 1, 0);
    glRotated(90, 1, 0, 0);
    glScaled(.15, .15, 3);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(6.25, 3, -17);
    glRotated(propRot, 1, 0, 0);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 1, 0);
    glScaled(.15, .15, 3);
    glutSolidCube(1);
    glPopMatrix();

    //Helicopter Tail Fins
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(5.75, 3, -16);
        glVertex3f(5.75, 3, -18);
        glVertex3f(5.75, 6, -17);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(5.75, 3, -16.5);
        glVertex3f(5.75, 3, -17.5);
        glVertex3f(5.75, 0, -17);
    glEnd();

    //Helicopter Landing Gear
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(6, 3, -4);
        glVertex3f(7, .75, -4);
        glVertex3f(6, 3, -8);
        glVertex3f(7, .75, -8);
        glVertex3f(7, .75, -3);
        glVertex3f(7, .75, -8);
        glVertex3f(6, 3, -4);
        glVertex3f(5, .75, -4);
        glVertex3f(6, 3, -8);
        glVertex3f(5, .75, -8);
        glVertex3f(5, .75, -3);
        glVertex3f(5, .75, -8);
    glEnd();
}

void drawGround() 
{
    //Landing Pad
    glColor3f(0.86666666666666666666666666666667, 0.24705882352941176470588235294118, 0.21568627450980392156862745098039);
    glPushMatrix();
    glTranslated(6, -.25, -9);
    glScaled(6, 1, 12);
    glutSolidCube(1);
    glPopMatrix();

    //Ground
    glColor3f(0.51764705882352941176470588235294, 0.46666666666666666666666666666667, 0.45490196078431372549019607843137);
    glPushMatrix();
    glTranslated(6, -.5, -9);
    glScaled(52, 1, 52);
    glutSolidCube(1);
    glPopMatrix();
}

void drawCar()
{
    //Car Body
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(13, 4, -4);
    glScaled(.5, 2, 3);
    glutSolidCube(1);
    glPopMatrix();

    //Car Cabin
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(13, 3.5, -2);
    glScaled(.5, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    //Driver Front Tire
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(13.5, 3.5, -3.0);
    glScaled(.15, .25, .25);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    //Driver Rear Tire
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(13.5, 3.5, -5.0);
    glScaled(.15, .25, .25);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    //Passenger Front Tire
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(12.5, 3.1, -2.5);
    glScaled(.15, .25, .25);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    //Passenger Rear Tire
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(12.5, 3.1, -5.0);
    glScaled(.15, .25, .25);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
}

void drawCones()
{
    //Green cone
    glColor3f(cone1ColorR, cone1ColorG, cone1ColorB);
    glPushMatrix();
    glTranslated(-2, 2, -4);
    glRotated(-90, 1, 0, 0);
    glutWireCone(1, 3, 20, 20);
    glPopMatrix();

    //Purple cone
    glColor3f(cone2ColorR, cone2ColorG, cone2ColorB);
    glPushMatrix();
    glTranslated(-.25, 2, -3);
    glRotated(-90, 1, 0, 0);
    glutWireCone(.5, 1.5, 20, 20);
    glPopMatrix();

    //Light blue cone
    glColor3f(cone3ColorR, cone3ColorG, cone3ColorB);
    glPushMatrix();
    glTranslated(-1.5, 2, -2);
    glRotated(-90, 1, 0, 0);
    glutWireCone(.5, 1, 20, 20);
    glPopMatrix();
}

void drawTree()
{
    glColor3f(0.50980392156862745098039215686275, 0.35686274509803921568627450980392, 0.1960784313725490196078431372549);
    glPushMatrix();
    glTranslated(12, 2, -17);
    glScaled(.15, 5, .5);
    glutSolidCube(1);
    glPopMatrix();
    
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(12, 5, -17);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
}

void drawHoop()
{
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-3, 2, -10);
    glScaled(.25, 25, .5);
    glutSolidCube(1);
    glPopMatrix();

    //Pink torus
    glColor3f(torusColorR, torusColorG, torusColorB);
    glPushMatrix();
    glTranslated(-3, 21, -10);
    glutWireTorus(1, 6, 30, 30);
    glPopMatrix();
}

void drawText()
{
    glColor3f(1, 0, 0);
    glRasterPos3f(3.0, 5.0, .7);
    //writeBitmapString(GLUT_BITMAP_8_BY_13, "Current Score: ");
}

void drawClickedText()
{
    glColor3f(1, 0, 0);
    glRasterPos3f(3.0, 5.0, .7);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "SELECTED!");
}

//Helicopter color pick will be red
void drawItems(void)
{
    glPushMatrix();
    glRotated(rotHeli, 0, 1, 0);
    glTranslated(xPosHeli, yPosHeli, zPosHeli);
    if (itemID == HELI)
    {
        drawClickedText();
        balloonAnimate = true;
    }
    if (selecting)
    {
        drawHeli(1.0, 0.0, 0.0);
    }
    else
    {
        drawHeli(0.94901960784313725490196078431373, 0.42352941176470588235294117647059, 0.07450980392156862745098039215686);
    }
    glPopMatrix();
    propAnimation();
    heliAnimation(1);
    balloonAnimation(1);
    checkCollision();
    cout << xPosHeli << endl;
    cout << yPosHeli << endl;
    cout << zPosHeli << endl;

    drawGround();

    glPushMatrix();
    glTranslated(0, -2, 4);
    drawCar();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -2, 2);
    drawCones();
    glPopMatrix();

    drawHoop();

    glPushMatrix();
    glTranslated(2, 0, 0);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2, 0, 4);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2, 0, 8);
    drawTree();
    glPopMatrix();

    drawText();
}

//Drawing to Screen Function
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    //View
    //South
    if (lookPos == 0) {
        gluLookAt(6, 5, 5,
            6, 5, -12,
            0, 1, 0);
        glutPostRedisplay();
    }

    //East
    if (lookPos == 1) {
        gluLookAt(18, 6, -6,
            6, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //North
    if (lookPos == 2) {
        gluLookAt(6, 8, -18,
            6, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //West
    if (lookPos == 3) {
        gluLookAt(-6, 6, -6,
            1, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //Overhead - TODO

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
    glClearColor(0.07450980392156862745098039215686, 0.62745098039215686274509803921569, 0.94901960784313725490196078431373, 0.0);
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

    case '3':
        lookPos = 0;
        break;

    case '2':
        lookPos = 1;
        break;

    case '1':
        lookPos = 2;
        break;

    case '4':
        lookPos = 3;
        break;

    case 'o':
        heliPower = !heliPower;
        break;

    case 'f':
        heliAnimate = !heliAnimate;
        break;

    default:
        break;
    }
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
    glutCreateWindow("Helicopter Bloon Dropper");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseInput);
    printInteraction();
    glutMainLoop();

    return 0;
}
//-------------------------------------------------------------------------------------------------------------//

