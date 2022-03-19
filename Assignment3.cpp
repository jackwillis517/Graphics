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
static int lookPos = 0;
static int propRot = 0;
static int act = 1;
static float heliSpeed = .0015;
static float rotHeli = 0;
static float xPosHeli = 0;
static float yPosHeli = 0;
static float zPosHeli = 0;
static bool heliPower = false;
static bool heliAnimate = false;


//Projection for entire project
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-4, 4, -4, 4, 1, 21);
    glMatrixMode(GL_MODELVIEW);
}


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

//-------------------------------------------------------------------------------------------------------------//


//---------------------------------------------Drawing Functions-----------------------------------------------//
void drawHeli()
{
    //Helicopter Body
    glColor3f(0.94901960784313725490196078431373, 0.42352941176470588235294117647059, 0.07450980392156862745098039215686);
    glPushMatrix();
    glTranslated(6, 3, -6);
    glScaled(2, 2, 3);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

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
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(-2, 2, -4);
    glRotated(-90, 1, 0, 0);
    glutWireCone(1, 3, 20, 20);
    glPopMatrix();

    glColor3f(0.76862745098039215686274509803922, 0.21568627450980392156862745098039, 0.86666666666666666666666666666667);
    glPushMatrix();
    glTranslated(-.25, 2, -3);
    glRotated(-90, 1, 0, 0);
    glutWireCone(.5, 1.5, 20, 20);
    glPopMatrix();

    glColor3f(0.0, 1.0, 1.0);
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

    glColor3f(0.98823529411764705882352941176471, 0.01960784313725490196078431372549, 0.63137254901960784313725490196078);
    glPushMatrix();
    glTranslated(-3, 21, -10);
    glutWireTorus(1, 6, 30, 30);
    glPopMatrix();
}

void writeBitmapString(void* font, const char* string)
{
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawText()
{
    glEnable(GL_DEPTH_TEST);
    glColor3f(1, 0, 0);
    glRasterPos3f(3.0, 5.0, .7);
    //writeBitmapString(GLUT_BITMAP_8_BY_13, "Current Score: ");
    glDisable(GL_DEPTH_TEST);

}
//-------------------------------------------------------------------------------------------------------------//
 

//Drawing to Screen Function
void drawScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    //Overhead


    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        glRotated(rotHeli, 0, 1, 0);
        glTranslated(xPosHeli, yPosHeli, zPosHeli);
        drawHeli();
    glPopMatrix();
    propAnimation();
    heliAnimation(1);
    
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

    glutSwapBuffers();
}


//Setup Screen Function
void setup(void)
{
    glClearColor(0.07450980392156862745098039215686, 0.62745098039215686274509803921569, 0.94901960784313725490196078431373, 0.0);
}

//Resize Screen Function
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    setProjection();
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

    case 'a':
        heliAnimate = !heliAnimate;
        break;

    

    default:
        break;
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
    printInteraction();
    glutMainLoop();

    return 0;
}

