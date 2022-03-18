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
static float xPosHeli = 0;
static float yPosHeli = 0;
static float zPosHeli = 0;
static bool heliPower = false;
static bool heliAct1 = false;
static bool heliAct2 = false;

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
void animateHeliAct1(void)
{
    if (yPosHeli < 10) {
        yPosHeli += .005;
    }

    if (yPosHeli == 10) {
        heliAct2 = true;
    }
    glutPostRedisplay();
}

void animateHeliAct2(void)
{
    if (xPosHeli > -2) {
        xPosHeli -= 1;
    }
    glutPostRedisplay();
}

void heliAnimation(int x)
{
    if (heliAct1) animateHeliAct1();

    if (heliAct2) animateHeliAct2();

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
    glScaled(.25, 5, .5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.98823529411764705882352941176471, 0.01960784313725490196078431372549, 0.63137254901960784313725490196078);
    glPushMatrix();
    glTranslated(-3, 11, -10);
    glutWireTorus(1, 6, 30, 30);
    glPopMatrix();
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
        gluLookAt(6, 5, 1,
            6, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //East
    if (lookPos == 1) {
        gluLookAt(15, 6, -6,
            10, 5, -6,
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
        gluLookAt(-4, 6, -6,
            1, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //Overhead


    glEnable(GL_DEPTH_TEST);


    glPushMatrix();
        /*glRotated(90, 0, 1, 0);*/
        glTranslated(xPosHeli, yPosHeli, 0);
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

    case 's':
        lookPos = 0;
        break;

    case 'e':
        lookPos = 1;
        break;

    case 'n':
        lookPos = 2;
        break;

    case 'w':
        lookPos = 3;
        break;

    case 'o':
        heliPower = !heliPower;
        break;

    case 'a':
        heliAct1 = !heliAct1;
        break;

    default:
        break;
    }
}

//Print Intructions Function
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press " << endl;
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

