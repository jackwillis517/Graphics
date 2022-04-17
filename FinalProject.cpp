/******************************************
*
* Official Name:  Jack Andrew Willis
*
* Call me: Jack
*
* E-mail:  jwilli59@syr.edu
*
* Assignment:  Final Project
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  May 5, 2022
*
* References: 
*
* Interactions:
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

using namespace std;
static int PI = 3.14159265358979324;
static float* vertices = NULL;
static int cylinderCols = 20;
static int cylinderRows = 4;

//Color picking globals
static int PAWNPINK1 = 1;
static int ROOKPINK1 = 2;
static int KINGPINK = 3;
static int QUEENPINK = 4;
static int PAWNPINK2 = 5;
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
static bool selecting = false;

//Light globals
static bool lightsOn = false;
static bool spotlightOn = false;
static bool flashlightFollow = false;
static int lightsClicked = 0;
static float globAmbVal = 0.8;

//Animation globals


//First person movement globals
static float fpX = 0.0;
static float fpY = 5.0;
static float fpZ = 28.0;
static float stepsize = 1;
static float rotsize = 5;
static float degrees = 188;
static bool canMove = true;

//Chess Pieces
static float pawnPinkX1 = 6;
static float pawnPinkY1 = 0;
static float pawnPinkZ1 = 2;
static float pawnPinkX2 = 12;
static float pawnPinkY2 = 0;
static float pawnPinkZ2 = 8;
static float rookPinkX1 = 0;
static float rookPinkY1 = 0;
static float rookPinkZ1 = 8;
static float kingPinkX = 10;
static float kingPinkY = 0;
static float kingPinkZ = 4;
static float QueenPinkX = 4;
static float QueenPinkY = 0;
static float QueenPinkZ = 6;

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

    if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 0) {
        itemID = PAWNPINK1;
        cout << "Pawn Pink 1 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 100 && (int)pixel[2] == 0) {
        itemID = ROOKPINK1;
        cout << "Rook Pink 1 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 200 && (int)pixel[2] == 0) {
        itemID = KINGPINK;
        cout << "King Pink selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 201 && (int)pixel[2] == 0) {
        itemID = QUEENPINK;
        cout << "Queen Pink selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 202 && (int)pixel[2] == 0) {
        itemID = PAWNPINK2;
        cout << "Pawn Pink 2 selected." << endl;
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
    
    glutPostRedisplay();
}

//Cylinder Functions
float f(int i, int j)
{
    return (cos((-1 + 2 * (float)i / cylinderCols) * PI));
}

float g(int i, int j)
{
    return (sin((-1 + 2 * (float)i / cylinderCols) * PI));
}

float h(int i, int j)
{
    return (-1 + 2 * (float)j / cylinderRows);
}

void fillVertexArray(void)
{
    int i, j, index;
    index = 0;
    for (j = 0; j <= cylinderRows; j++) {
        for (i = 0; i <= cylinderCols; i++)
        {
            vertices[index++] = f(i, j);
            vertices[index++] = g(i, j);
            vertices[index++] = h(i, j);
        }
    }
}

void glutSolidCylinder()
{
    int  i, j;
    vertices = new float[315];
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    fillVertexArray();
    
    for (j = 0; j < cylinderRows; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= cylinderCols; i++)
        {
            glArrayElement((j + 1) * (cylinderCols + 1) + i);
            glArrayElement(j * (cylinderCols + 1) + i);
        }
        glEnd();
    }
}
//--------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Animations-------------------------------------------------------//







//-------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Drawing Functions-----------------------------------------------//
void drawGround()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glPushMatrix();
    glTranslated(0, -1, 0);
    glScaled(50, 1, 50);
    glutSolidCube(1);
    glPopMatrix();
}

void drawBoardSquare(int x, int z)
{
    glPushMatrix();
    glTranslated(x, 0, z);
    glScaled(2, 0.25, 2);
    glutSolidCube(1);
    glPopMatrix();
}

void drawPawnPink1()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslated(pawnPinkX1, pawnPinkY1 + 1, pawnPinkZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder();
    glPopMatrix();

    //Cube used to patch hole in cylinder
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glPushMatrix();
    glTranslated(pawnPinkX1 - .31, pawnPinkY1 + 1, pawnPinkZ1);
    glScaled(.05, 1.25, .15);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnPinkX1, pawnPinkY1 + .4, pawnPinkZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.1, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnPinkX1, pawnPinkY1 + 2, pawnPinkZ1);
    glRotated(90, 1, 0, 0);
    glutSolidSphere(.5, 25, 25);
    glPopMatrix();
}

void drawPawnPink2()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 202, 0);
    glPushMatrix();
    glTranslated(pawnPinkX2, pawnPinkY2 + 1, pawnPinkZ2);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder();
    glPopMatrix();

    //Cube used to patch hole in cylinder
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glPushMatrix();
    glTranslated(pawnPinkX2 - .31, pawnPinkY2 + 1, pawnPinkZ2);
    glScaled(.05, 1.25, .15);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnPinkX2, pawnPinkY2 + .4, pawnPinkZ2);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.1, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnPinkX2, pawnPinkY2 + 2, pawnPinkZ2);
    glRotated(90, 1, 0, 0);
    glutSolidSphere(.5, 25, 25);
    glPopMatrix();
}

void drawRookPink1()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 100, 0);
    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + 1, rookPinkZ1);
    glScaled(.5, .75, .5);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + .4, rookPinkZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + 2, rookPinkZ1);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
}

void drawKingPink()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 200, 0);
    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + 1, kingPinkZ);
    glScaled(.5, 2.5, .5);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + .4, kingPinkZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + 3.65, kingPinkZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.45, 2, 25, 25);
    glPopMatrix();
}

void drawQueenPink()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 201, 0);
    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + 1, QueenPinkZ);
    glScaled(.5, 2, .5);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + .4, QueenPinkZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + 3, QueenPinkZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 2, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + 3.25, QueenPinkZ);
    glRotated(90, 1, 0, 0);
    glutSolidSphere(.6, 25, 25);
    glPopMatrix();
}

void drawChessboard()
{
    int count = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        drawBoardSquare(i, 0);
        count++;
    }

    int count2 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count2 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        drawBoardSquare(i, 2);
        count2++;
    }

    int count3 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count3 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        drawBoardSquare(i, 4);
        count3++;
    }

    int count4 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count4 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        drawBoardSquare(i, 6);
        count4++;
    }


    int count5 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count5 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        drawBoardSquare(i, 8);
        count5++;
    }

    int count6 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count6 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        drawBoardSquare(i, 10);
        count6++;
    }

    int count7 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count7 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        drawBoardSquare(i, 12);
        count7++;
    }

    int count8 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count8 % 2 == 0) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        }
        else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        }
        drawBoardSquare(i, 14);
        count8++;
    }
    
}



void drawItems()
{
    drawRookPink1();
    drawPawnPink2();
    drawPawnPink1();
    drawKingPink();
    drawQueenPink();
    drawChessboard();
    drawGround();
    checkCollision();
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
    
    glEnableClientState(GL_VERTEX_ARRAY);

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

    case '>':
        globAmbVal += 0.1;
        break;

    case '<':
        globAmbVal -= 0.1;
        break;

    case 'q':
        fpY -= stepsize;
        break;

    case 'e':
        fpY += stepsize;
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) selecting = false;
}

void mouseMotion(int x, int y)
{
    if (selecting && itemID == PAWNPINK1)
    {
        pawnPinkX1 = x;
        pawnPinkY1 = height - y;
        glutPostRedisplay();
    } 
} // end mouseMotion



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
    glutCreateWindow("Chess Game");
    setup();
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(keyInputSpecial);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseInput);
    glutMotionFunc(mouseMotion);
    printInteraction();
    glutMainLoop();

    return 0;
}
//-------------------------------------------------------------------------------------------------------------//

