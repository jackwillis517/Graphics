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
* Date submitted:  May 3, 2022
*
* References: 
* sketchuptextureclub.com
* dreamstime.com
* Interactions:
*******************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <random>
#include <ctime>
#include<cmath>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define ONE_BY_ROOT_THREE 0.57735

using namespace std;
static int PI = 3.14159265358979324;
static bool play = false;
static GLUquadricObj* qobj;
static unsigned int texture[6];
static bool cafeScene = true;
static bool hollywoodScene = false;
static int turnCounter = 1;
static int clockX1 = -4.85;
static int clockY1 = 3.5;
static int clockZ1 = 3;
static int clockX2 = -4.85;
static int clockY2 = 3.5;
static int clockZ2 = 10.0;

//Color picking globals
static int PAWNPINK1 = 1;
static int ROOKPINK1 = 2;
static int KINGPINK = 3;
static int QUEENPINK = 4;
static int PAWNPINK2 = 5;
static int KINGGREEN = 6;
static int ROOKGREEN1 = 7;
static int ROOKGREEN2 = 8;
static int PAWNGREEN1 = 9;
static int PAWNGREEN2 = 10;
static int BISHOPGREEN1 = 11;
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
bool selecting = false;
bool dragging = false;

//Light globals
static bool lightsOn = false;
static bool spotlightOn = false;
static bool flashlightFollow = false;
static int lightsClicked = 0;
static float globAmbVal = 0.8;

//Animation globals


//First person movement globals
static float fpX = 0.0;
static float fpY = 7.0;
static float fpZ = 28.0;
static float fpX2 = 6.5;
static float fpY2 = 7.0;
static float fpZ2 = 28.0;
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

static float kingGreenX = 6;
static float kingGreenY = 0;
static float kingGreenZ = 14;
static float rookGreenX1 = 0;
static float rookGreenY1 = 0;
static float rookGreenZ1 = 14;
static float rookGreenX2 = 6;
static float rookGreenY2 = 0;
static float rookGreenZ2 = 10;
static float pawnGreenX1 = 10;
static float pawnGreenY1 = 0; 
static float pawnGreenZ1 = 12;
static float pawnGreenX2 = 14;
static float pawnGreenY2 = 0;
static float pawnGreenZ2 = 8;
static float bishopGreenX1 = 8;
static float bishopGreenY1 = 0;
static float bishopGreenZ1 = 10;

double xred = 6;
double yred = 0;
double zred = 2;

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

//Bezier Surface Coords
static float controlPoints[6][4][3] =
{
    {{-3, 12.5, 5}, {-0.25, 12.5, 5}, {0.25, 12.5, 5}, {3, 12.5, 5}},
    {{-3.0, 0.0, 3.0}, {-0.25, 0.0, 3.0}, {0.25, 0.0, 3.0}, {3.0, 0.0, 3.0}},
    {{-3.0, 0.0, 1.0}, {-0.25, 0.0, 1.0}, {0.25, 0.0, 1.0}, {3.0, 0.0, 1.0}},
    {{-3.0, 0.0, -1.0}, {-0.25, 0.0, -1.0}, {0.25, 0.0, -1.0}, {3.0, 0.0, -1.0}},
    {{-3.0, 0.0, -3.0}, {-0.25, 0.0, -3.0}, {0.25, 0.0, -3.0}, {3.0, 0.0, -3.0}},
    {{-3, 12.5, -5}, {-0.25, 12.5, -5}, {0.25, 12.5, -5}, {3, 12.5, -5}},
};

//---------------------------------------------Utility Functions------------------------------------------------//
//Projection for entire project
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (play) {
        glOrtho(-15.0, 15.0, -15.0, 15.0, 1, 100);
    }
    else {
        gluPerspective(120, 1, 1, 100);
    }
    glMatrixMode(GL_MODELVIEW);
}

//Identification function for color picking
void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 0 && (int)pixel[1] == 200 && (int)pixel[2] == 0) {
        itemID = PAWNPINK1;
        cout << "Pawn Pink 1 selected." << endl;
        cout << selecting << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 201 && (int)pixel[2] == 0) {
        itemID = ROOKPINK1;
        cout << "Rook Pink 1 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 202 && (int)pixel[2] == 0) {
        itemID = KINGPINK;
        cout << "King Pink selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 203 && (int)pixel[2] == 0) {
        itemID = QUEENPINK;
        cout << "Queen Pink selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 204 && (int)pixel[2] == 0) {
        itemID = PAWNPINK2;
        cout << "Pawn Pink 2 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 205 && (int)pixel[2] == 0) {
        itemID = KINGGREEN;
        cout << "King Green selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 206 && (int)pixel[2] == 0) {
        itemID = ROOKGREEN1;
        cout << "Rook Green 1 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 207 && (int)pixel[2] == 0) {
        itemID = ROOKGREEN2;
        cout << "Rook Green 2 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 208 && (int)pixel[2] == 0) {
        itemID = PAWNGREEN1;
        cout << "Pawn Green 1 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 209 && (int)pixel[2] == 0) {
        itemID = PAWNGREEN2;
        cout << "Pawn Green 2 selected." << endl;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 210 && (int)pixel[2] == 0) {
        itemID = BISHOPGREEN1;
        cout << "Bishop Green 1 selected." << endl;
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

//BitMapFile Struct
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char* data;
};

//Runction to read a bitmap file.
BitMapFile* getBMPData(string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;

    // Read input file name.
    ifstream infile(filename.c_str(), ios::binary);

    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char*)&offset, 4);

    // Get the header size of the bitmap.
    infile.read((char*)&headerSize, 4);

    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read((char*)&bmp->sizeX, 4);
    infile.read((char*)&bmp->sizeY, 4);

    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];

    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char*)bmp->data, size);

    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i + 2];
        bmp->data[i + 2] = temp;
    }

    return bmp;
}

//Load external textures.
void loadExternalTextures()
{
    //Local storage for bmp image data.
    BitMapFile* image[6];

    //Textures.
    image[0] = getBMPData("Textures/cherrywood.bmp");
    image[1] = getBMPData("Textures/mahogany.bmp");
    image[2] = getBMPData("Textures/gold.bmp");
    image[3] = getBMPData("Textures/silver.bmp");
    image[4] = getBMPData("Textures/star.bmp");
    image[5] = getBMPData("Textures/marble.bmp");

    //Cherrywood image to texture index[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);

    //Mahogany image to texture index[1]
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);

    //Gold image to texture index[2]
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[2]->sizeX, image[2]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);

    //Silver image to texture index[3]
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[3]->sizeX, image[3]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);

    //Star image to texture index[4].
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[4]->sizeX, image[4]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[4]->data);

    //Marble image to texture index[5].
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[5]->sizeX, image[5]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[5]->data);
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

void drawClockRest()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glPushMatrix();
    glTranslated(-4, 0, .25);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    glScaled(.5, .5, .5);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4, 0, 12.75);
    glRotated(-90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    glScaled(.5, .5, .5);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
    glPushMatrix();
    glTranslated(-4, 0, 6.5);
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f(2.5, 1.5, -6.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-2.5, 1.5, -6.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-2.5, 1.5, 6.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(2.5, 1.5, 6.0);
    glEnd();
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glPushMatrix();
    glTranslated(-4.0, 3, 6.5);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.5, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glPushMatrix();
    glTranslated(-6.0, 2.0, 0.8);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 0.5, 50, 50);
    glPopMatrix();

    
    glPushMatrix();
    glTranslated(-2.0, 2.0, 0.8);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 0.5, 50, 50);
    glPopMatrix();

    
    glPushMatrix();
    glTranslated(-6.0, 2.0, 12.2);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 0.5, 50, 50);
    glPopMatrix();

    
    glPushMatrix();
    glTranslated(-2.0, 2.0, 12.2);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 0.5, 50, 50);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawClocks()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
    glTranslated(clockX1, clockY1, clockZ1);
    glRotated(90, 0, 1, 0);
    gluCylinder(qobj, 1.5, 1.5, 1.5, 40, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(clockX1, clockY1, clockZ1);
    glRotated(90, 0, 1, 0);
    gluDisk(qobj, 0.0, 1.5, 40, 4);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(clockX1 + 1, clockY1, clockZ1);
    glRotated(90, 0, 1, 0);
    gluDisk(qobj, 0.15, 1.45, 40, 4);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawClocks2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
    glTranslated(clockX2, clockY2, clockZ2);
    glRotated(90, 0, 1, 0);
    gluCylinder(qobj, 1.5, 1.5, 1.5, 40, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(clockX2, clockY2, clockZ2);
    glRotated(90, 0, 1, 0);
    gluDisk(qobj, 0.0, 1.5, 40, 4);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslated(clockX2 + 1, clockY2, clockZ2);
    glRotated(90, 0, 1, 0);
    gluDisk(qobj, 0.15, 1.45, 40, 4);
    glPopMatrix();


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawCoffeeCup()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslated(20.0, 4.5, 5.0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 2.5, 2.5, 5.0, 40, 5);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
    glTranslated(20.0, 4.5, 5.0);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 2.25, 2.25, 5.0, 40, 5);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslated(20.0, 0.05, 5.0);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 0.0, 2.25, 40, 4);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glTranslated(20.0, 4.5, 5.0);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 2.15, 2.5, 40, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(20.0, 3.25, 2.0);
    glScaled(0.5, 0.5, 1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(20.0, 0.5, 2.0);
    glScaled(0.5, 0.5, 1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(20.0, 1.88, 1.5);
    glRotated(90, 1, 0, 0);
    glScaled(0.5, 0.5, 3.25);
    glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawNewtonsCraddle()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(10.0, 0.0, -10.0);
    glScaled(13.0, 0.5, 5.0);
    glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawBoardSquare1(float x, float z)
{
    glEnable(GL_TEXTURE_2D);
    if (hollywoodScene) {
        glBindTexture(GL_TEXTURE_2D, texture[5]);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, texture[1]);
    }
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f(x - 1.0, 0.12, z - 1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(x + 1.0, 0.12, z - 1.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(x + 1.0, 0.12, z + 1.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(x - 1.0, 0.12, z + 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawBoardSquare2(float x, float z)
{
    glEnable(GL_TEXTURE_2D);
    if (hollywoodScene) {
        glBindTexture(GL_TEXTURE_2D, texture[4]);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, texture[0]);
    }
    glNormal3f(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(x - 1.0, 0.12, z - 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(x + 1.0, 0.12, z - 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(x + 1.0, 0.12, z + 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(x - 1.0, 0.12, z + 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawChessboard()
{
    int count = 0;
    glColor3ub(202, 202, 0);
    for (int i = 0; i < 16; i += 2) {
        if (count % 2 == 0) {
            drawBoardSquare1(i, 0);
        }
        else {
            drawBoardSquare2(i, 0);
        }
        count++;
    }

    int count2 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count2 % 2 == 0) {
            drawBoardSquare2(i, 2);
        }
        else {
            drawBoardSquare1(i, 2);
        }
        count2++;
    }

    int count3 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count3 % 2 == 0) {
            drawBoardSquare1(i, 4);
        }
        else {
            drawBoardSquare2(i, 4);
        }
        count3++;
    }

    int count4 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count4 % 2 == 0) {
            drawBoardSquare2(i, 6);
        }
        else {
            drawBoardSquare1(i, 6);
        }
        count4++;
    }


    int count5 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count5 % 2 == 0) {
            drawBoardSquare1(i, 8);
        }
        else {
            drawBoardSquare2(i, 8);
        }
        count5++;
    }

    int count6 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count6 % 2 == 0) {
            drawBoardSquare2(i, 10);
        }
        else {
            drawBoardSquare1(i, 10);
        }
        count6++;
    }

    int count7 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count7 % 2 == 0) {
            drawBoardSquare1(i, 12);
        }
        else {
            drawBoardSquare2(i, 12);
        }
        count7++;
    }

    int count8 = 0;
    for (int i = 0; i < 16; i += 2) {
        if (count8 % 2 == 0) {
            drawBoardSquare2(i, 14);
        }
        else {
            drawBoardSquare1(i, 14);
        }
        count8++;
    }

}

void drawPawnPink1()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 200, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    }
    glPushMatrix();
    glTranslated(pawnPinkX1, pawnPinkY1 + .25, pawnPinkZ1);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.4, 0.2, 1.5, 15, 5);
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
    gluSphere(qobj, .5, 50, 50);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
    
}

void drawRookPink1()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 201, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    }
    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + .25, rookPinkZ1);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.4, 1.5, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + .4, rookPinkZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookPinkX1, rookPinkY1 + 2.2, rookPinkZ1);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawKingPink()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 202, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    }
    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + .25, kingPinkZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.5, 3.25, 15, 5);
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
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawQueenPink()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 203, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    }
    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + .25, QueenPinkZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.5, 3.25, 15, 5);
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
    gluSphere(qobj, .6, 15, 10);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawPawnPink2()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glColor3ub(0, 204, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
    }
    glPushMatrix();
    glTranslated(pawnPinkX2, pawnPinkY2 + .25, pawnPinkZ2);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.4, 0.2, 1.5, 15, 5);
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
    gluSphere(qobj, .5, 50, 50);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawKingGreen()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 205, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(kingGreenX, kingGreenY + .25, kingGreenZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.5, 3.25, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(kingGreenX, kingGreenY + .4, kingGreenZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(kingGreenX, kingGreenY + 3.65, kingGreenZ);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.45, 2, 25, 25);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawRookGreen1()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 206, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(rookGreenX1, rookGreenY1 + .25, rookGreenZ1);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.4, 1.5, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookGreenX1, rookGreenY1 + .4, rookGreenZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookGreenX1, rookGreenY1 + 2.2, rookGreenZ1);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawRookGreen2()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 207, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glPushMatrix();
    glTranslated(rookGreenX2, rookGreenY2 + .25, rookGreenZ2);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.4, 1.5, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookGreenX2, rookGreenY2 + .4, rookGreenZ2);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.5, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(rookGreenX2, rookGreenY2 + 2.2, rookGreenZ2);
    glRotated(90, 1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawPawnGreen1()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 208, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(pawnGreenX1, pawnGreenY1 + .25, pawnGreenZ1);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.4, 0.2, 1.5, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnGreenX1, pawnGreenY1 + .4, pawnGreenZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.1, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnGreenX1, pawnGreenY1 + 2, pawnGreenZ1);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, .5, 50, 50);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawPawnGreen2()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 209, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(pawnGreenX2, pawnGreenY2 + .25, pawnGreenZ2);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.4, 0.2, 1.5, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnGreenX2, pawnGreenY2 + .4, pawnGreenZ2);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.35, 1.1, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(pawnGreenX2, pawnGreenY2 + 2, pawnGreenZ2);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, .5, 50, 50);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawBishopGreen1()
{
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glColor3ub(0, 210, 0);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(bishopGreenX1, bishopGreenY1 + .25, bishopGreenZ1);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.4, 0.2, 2.5, 15, 5);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }

    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    if (!selecting) {
        glEnable(GL_TEXTURE_2D);
        if (hollywoodScene) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
    }
    glPushMatrix();
    glTranslated(bishopGreenX1, bishopGreenY1 + .4, bishopGreenZ1);
    glScaled(.35, .75, .35);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(.45, 1.1, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslated(bishopGreenX1, bishopGreenY1 + 3, bishopGreenZ1);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, .5, 50, 50);
    glPopMatrix();
    if (!selecting) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawBoardBoarder()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(-1.0, 0.0, 7.0);
    glScaled(0.25, 0.25, 16);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(15.0, 0.0, 7.0);
    glScaled(0.25, 0.25, 16);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(7.0, 0.0, -1.0);
    glRotated(90, 0, 1, 0);
    glScaled(0.25, 0.25, 16.25);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(7.0, 0.0, 15.0);
    glRotated(90, 0, 1, 0);
    glScaled(0.25, 0.25, 16.25);
    glutSolidCube(1);
    glPopMatrix();
}

void drawRedBox()
{
    //red cube
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslatef(xred, yred, zred);
    //draw a red cube
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawItems()
{
    drawChessboard();
    drawBoardBoarder();
    drawGround();
    drawClockRest();
    drawClocks();
    drawClocks2();
    drawCoffeeCup();
    drawNewtonsCraddle();
    drawRedBox();

    drawRookPink1();
    drawPawnPink2();
    drawPawnPink1();
    drawKingPink();
    drawQueenPink();
    drawKingGreen();
    drawRookGreen1();
    drawRookGreen2();
    drawPawnGreen1();
    drawPawnGreen2();
    drawBishopGreen1();

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
    if (play) {
        if (turnCounter % 2 != 0) {
            gluLookAt(fpX2, fpY2 + 7, fpZ2,
                fpX2 + sin(188.0 * PI / 180), fpY2 + 6, fpZ2 + cos(188.0 * PI / 180),
                0, 1, 0);
        }
        else {
            gluLookAt(fpX2, fpY2 + 17, fpZ2 - 50,
                fpX2 + sin(188.0 * PI / 180), fpY2 - 15, fpZ2 + cos(188.0 * PI / 180),
                0, 1, 0);
        }
    }
    else {
        gluLookAt(fpX, fpY, fpZ,
            fpX + sin(degrees * PI / 180), fpY, fpZ + cos(degrees * PI / 180),
            0, 1, 0);
    }

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
    
    //Create texture index array.
    glGenTextures(6, texture);

    //Load external textures.
    loadExternalTextures();

    //Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);

    //Enable Quadrics
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, true);

    //Enable the Bezier surfaces
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints[0][0]);
    glEnable(GL_MAP2_VERTEX_3);

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
        if (canMove) {
            fpY -= stepsize;
        }
        break;

    case 'e':
        if (canMove) {
            fpY += stepsize;
        }
        break;

    case 'p':
        play = !play;
        canMove = !canMove;
        break;

    case '1':
        hollywoodScene = !hollywoodScene;
        cafeScene = !cafeScene;
        break;

    case 't':
        turnCounter++;
        cout << "Turn Number: " << turnCounter << endl;
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
        if (canMove) {
            degrees -= rotsize;
        }
        break;

    case GLUT_KEY_LEFT:
        if (canMove) {
            degrees += rotsize;
        }
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

void mouseInput(int button, int state, int x, int y)
{
    /*if (state == GLUT_DOWN && button == GLUT_LEFT) {
        selecting = true;
        xMouse = x;
        yMouse = height - y;
        glutPostRedisplay();
    }*/
    if (button == GLUT_LEFT && state == GLUT_DOWN) //mouse clicked
    {
        std::cout << "left button pressed" << std::endl;
        selecting = true;
        xMouse = x;
        yMouse = height - y;

        //conversion factors
        double fw = 30.0 / width;
        double fh = -30.0 / height;  //note - since in z neg above pos

        double a = x * fw;
        double b = (height - y) * fh;

        //window coordinates
        double xW = fpX2 + -15 + a;
        double zW = fpZ2 + b;  //z instead of y

        std::cout << "xW=" << xW << ' ' << "zW=" << zW << std::endl;
        cout << "xred=" << xred << ' ' << "zred=" << zred << endl;
        //if click is in red box
        if (xW <= xred + 1 && xW >= xred - 1 && zW <= zred + 2.5 && zW >= zred - 2.5)  //z instead of y
        {
            dragging = true;
            std::cout << "dragging" << std::endl;
        }
        else {
            dragging = false;
        }

        glutPostRedisplay();

    }
    /*if (state == GLUT_UP && button == GLUT_LEFT) {
        selecting = false;
        itemID = 0;
    }*/

    
    if (button == GLUT_LEFT && state == GLUT_UP) {
        selecting = false;
        itemID = 0;
        dragging = false;
    } 

} //end mouseControlFunction


void mouseMotion(int x, int y)
{
    if (dragging)
    {
        //conversion factors
        double fw = 30.0 / width;
        double fh = -30.0 / height;  //note - since in z neg above pos

        double a = x * fw;
        double b = (height - y) * fh;
        double xW = fpX2 + -15 + a;
        double zW = fpZ2 + 15 + b;    //z instead of y
        std::cout << "xW=" << xW << ' ' << "zW=" << zW << std::endl;

        //give red cube world coordinates of the mouse
        xred = xW;
        zred = zW - 15.5;  //z instead of y
        pawnPinkX1 = xred;
        pawnPinkZ1 = zred;

        glutPostRedisplay();
    } // end of dragging
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

