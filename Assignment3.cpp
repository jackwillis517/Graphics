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
static int lookPos = 0;

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-4, 4, -4, 4, 1, 21);
    glMatrixMode(GL_MODELVIEW);
}

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
    glScaled(.25, .25, 10);
    glutSolidCube(1);
    glPopMatrix();

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

// Drawing routine.
void drawScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //View
    //South
    if (lookPos == 0) {
        gluLookAt(6, 5, 0,
            6, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }
    

    //East
    if (lookPos == 1) {
        gluLookAt(12, 5, -6,
            10, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //North
    if (lookPos == 2) {
        gluLookAt(6, 5, -18,
            6, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //West
    if (lookPos == 3) {
        gluLookAt(-5, 7, -6,
            -1, 5, -6,
            0, 1, 0);
        glutPostRedisplay();
    }

    //Overhead


     
    glEnable(GL_DEPTH_TEST);

    glColor3f(.8, 1.0, .8);
    glPushMatrix();
    glTranslated(6, -.5, -9);
    glScaled(24, 1, 12);
    glutSolidCube(1);
    glPopMatrix();

    drawHeli();

    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.07450980392156862745098039215686, 0.62745098039215686274509803921569, 0.94901960784313725490196078431373, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    setProjection();
}

// Keyboard input processing routine.
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

    default:
        break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press " << endl;
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
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

