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

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-15, 15, -15, 15, 1, 15);
    glMatrixMode(GL_MODELVIEW);
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
     /*gluLookAt(1, 6, 2,
              1, 6, -6,
              0, 1, 0);*/

    //East
    /*gluLookAt(14, 6, -7,
              10, 6, -7,
              0, 1, 0);*/

    //North
    gluLookAt(1, 6, -17,
              1, 6, -9,
              0, 1, 0);

    //West


    //Overhead


    


     
    glEnable(GL_DEPTH_TEST);

    glColor3f(0.27843137254901960784313725490196, 0.26274509803921568627450980392157, 0.27058823529411764705882352941176);
    glPushMatrix();
    glTranslated(1, -1, 0);
    glScaled(25, 1, 8);
    glutSolidCube(1);
    glPopMatrix();

    //Orange wire sphere
    glColor3f(0.94901960784313725490196078431373, 0.42352941176470588235294117647059, 0.07450980392156862745098039215686);
    glPushMatrix();
    glTranslated(0, 2, -1);
    glScaled(2, 5, 2);
    glutWireSphere(1, 25, 25);
    glPopMatrix();

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

