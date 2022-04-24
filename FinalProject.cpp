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
* freecreatives.com
* stackoverflow.com
* colourbox.dk
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
static unsigned int texture[15];
static int sceneCounter = 1;
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
static float globAmbVal = 0.2;
static bool sun = false;
static bool lamp = false;

//Animation globals
static int act = 1; 
static bool newtonAnimate = false;

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
double xblue = 12;
double yblue = 0;
double zblue = 8;
double xgreen = 0;
double ygreen = 0;
double zgreen = 8;
double xorange = 10;
double yorange = 0;
double zorange = 4;
double xpurple = 4;
double ypurple = 0;
double zpurple = 6;
double xblack = 6;
double yblack = 0;
double zblack = 14;
double xgrey = 0;
double ygrey = 0;
double zgrey = 14;
double xdarkgrey = 6;
double ydarkgrey = 0;
double zdarkgrey = 10;
double xyellow = 10;
double yyellow = 0;
double zyellow = 12;
double xbrown = 14;
double ybrown = 0;
double zbrown = 8;
double xwhite = 8;
double ywhite = 0;
double zwhite = 10;

//Newtons Craddle

static float ballX1 = 6.0;
static float ballY1 = 3.0;
static float ballZ1 = -10.0;

static float ballX2 = 8.0;
static float ballY2 = 3.0;
static float ballZ2 = -10.0;

static float ballX3 = 10.0;
static float ballY3 = 3.0;
static float ballZ3 = -10.0;

static float ballX4 = 12.0;
static float ballY4 = 3.0;
static float ballZ4 = -10.0;

static float ballX5 = 14.0;
static float ballY5 = 3.0;
static float ballZ5 = -10.0;

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
    BitMapFile* image[15];

    //Textures.
    image[0] = getBMPData("Textures/cherrywood.bmp");
    image[1] = getBMPData("Textures/mahogany.bmp");
    image[2] = getBMPData("Textures/gold.bmp");
    image[3] = getBMPData("Textures/silver.bmp");
    image[4] = getBMPData("Textures/star.bmp");
    image[5] = getBMPData("Textures/marble.bmp");
    image[6] = getBMPData("Textures/walnut.bmp");
    image[7] = getBMPData("Textures/chrome.bmp");
    image[8] = getBMPData("Textures/stoneblock.bmp");
    image[9] = getBMPData("Textures/stonewall.bmp");
    image[10] = getBMPData("Textures/obsidian.bmp");
    image[11] = getBMPData("Textures/lava.bmp");

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

    //Walnut image to texture index[6].
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[6]->sizeX, image[6]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[6]->data);

    //Chrome image to texture index[7].
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[7]->sizeX, image[7]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[7]->data);

    //Stoneblock image to texture index[8].
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[8]->sizeX, image[8]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[8]->data);

    //Stonewall image to texture index[9].
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[9]->sizeX, image[9]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[9]->data);

    //Obsidian image to texture index[10].
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[10]->sizeX, image[10]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[10]->data);
    
    //Lava image to texture index[11].
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[11]->sizeX, image[11]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[11]->data);
}
//--------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Animations-------------------------------------------------------//
void animateNewton() //acts here
{
    if (act == 1) {
        if (ballX1 > 0) {
            ballX1 -= .0005;
            ballY1 += .0001;
        }
        else {
            act = 2;
        }
    }

    if (act == 2) {
        if (ballX1 < 6) {
            ballX1 += .0005;
            ballY1 -= .0001;
        }
        else {
            act = 3;
        }
    }

    if (act == 3) {
        if (ballX5 < 20) {
            ballX5 += .0005;
            ballY5 += .0001;
        }
        else {
            act = 4;
        }
    }

    if (act == 4) {
        if (ballX5 > 14) {
            ballX5 -= .0005;
            ballY5 -= .0001;
        }
        else {
            act = 1;
        }
    }
    
}

void NewtonAnimation(int x)
{
    if (newtonAnimate) animateNewton();
    glutTimerFunc(100, NewtonAnimation, 1);
}
//-------------------------------------------------------------------------------------------------------------//



//---------------------------------------------Drawing Functions-----------------------------------------------//
void drawGround()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glPushMatrix();
    glTranslated(5, -1, 0);
    glScaled(40, 1, 35);
    glutSolidCube(1);
    glPopMatrix();
}

void drawWalls()
{
    //glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-35.0, 0.0, -40.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-35.0, -25.0, -40.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-35.0, -25.0, 40.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-35.0, 0.0, 40.0);
    glEnd();
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-35.0, 60.0, -40.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-35.0, 35.0, -40.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-35.0, 35.0, 40.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-35.0, 60.0, 40.0);
    glEnd();
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-35.0, -25.0, 25.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-35.0, 35.0, 25.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-35.0, 35.0, 40.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-35.0, -25.0, 40.0);
    glEnd();
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-35.0, -25.0, -25.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-35.0, 35.0, -25.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-35.0, 35.0, -40.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-35.0, -25.0, -40.0);
    glEnd();
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-35.0, -25.0, -10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-35.0, 35.0, -10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-35.0, 35.0, 10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-35.0, -25.0, 10.0);
    glEnd();


    glPushMatrix();
    glTranslated(-40.0, -30.0, -40.0);
    glScaled(100.0, 100.0, 25.0);
    double n = 100.0;
    glNormal3f(0.0, 0.0, 1.0);
    for (int r = 0; r < n; r++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= n; c++)
        {
            glVertex3f(c / n, r / n, 0.0);
            glVertex3f(c / n, (r + 1) / n, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(-40.0, -30.0, 40.0);
    glScaled(100.0, 100.0, 25.0);
    double j = 100.0;
    glNormal3f(0.0, 0.0, 1.0);
    for (int r = 0; r < j; r++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= j; c++)
        {
            glVertex3f(c / j, r / j, 0.0);
            glVertex3f(c / j, (r + 1) / j, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(40.0, -30.0, 40.0);
    glRotated(90, 0, 1, 0);
    glScaled(100.0, 100.0, 25.0);
    double k = 100.0;
    glNormal3f(0.0, 0.0, 1.0);
    for (int r = 0; r < k; r++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= k; c++)
        {
            glVertex3f(c / k, r / k, 0.0);
            glVertex3f(c / k, (r + 1) / k, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(-40.0, -20.0, -40.0);
    glRotated(90, 1, 0, 0);
    glScaled(100.0, 100.0, 25.0);
    double q = 100.0;
    glNormal3f(0.0, -1.0, 0.0);
    for (int r = 0; r < q; r++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= q; c++)
        {
            glVertex3f(c / q, r / q, 0.0);
            glVertex3f(c / q, (r + 1) / q, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(-40.0, 50.0, -40.0);
    glRotated(90, 1, 0, 0);
    glScaled(100.0, 100.0, 25.0);
    double w = 100.0;
    glNormal3f(0.0, 1.0, 0.0);
    for (int r = 0; r < w; r++)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
        glBegin(GL_TRIANGLE_STRIP);
        for (int c = 0; c <= w; c++)
        {
            glVertex3f(c / w, r / w, 0.0);
            glVertex3f(c / w, (r + 1) / w, 0.0);
        }
        glEnd();
    }
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    //glDisable(GL_TEXTURE_2D);
}

void drawLamp()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
    glTranslated(-7.0, 15, -10);
    glRotated(45, 0, 1, 0);
    glRotated(45, 1, 0, 0);
    gluCylinder(qobj, 1.5, 3, 5.0, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-7.0, 0, -10);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 0.0, 4, 40, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-7.0, 1, -10);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 0.5, 4, 40, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glPushMatrix();
    glTranslated(-7.0, 1, -10);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, 4, 4, 1.0, 40, 5);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslated(-7.0, 15, -10);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8.75, 5, -11.5);
    glRotated(45, 0, 1, 0);
    glRotated(-35, 1, 0, 0);
    glScaled(0.75, 10, 0.75);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8.75, 12, -11.5);
    glRotated(45, 0, 1, 0);
    glRotated(35, 1, 0, 0);
    glScaled(0.75, 10, 0.75);
    glutSolidCube(1);
    glPopMatrix();

    if (lamp) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    }
    
    glPushMatrix();
    glTranslated(-5.5, 13, -8);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.75, 50, 50);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
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

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
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

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
    glTranslated(4.0, 9.0, -7.75);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, .20, .20, 9.0, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.0, 9.0, -12.25);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, .20, .20, 9.0, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(16.0, 9.0, -7.75);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, .20, .20, 9.0, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(16.0, 9.0, -12.25);
    glRotated(90, 1, 0, 0);
    gluCylinder(qobj, .20, .20, 9.0, 40, 5);
    glPopMatrix();

    /*glPushMatrix();
    glTranslated(16.0, 9.0, -12.5);
    gluCylinder(qobj, .20, .20, 5.0, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.0, 9.0, -12.5);
    gluCylinder(qobj, .20, .20, 5.0, 40, 5);
    glPopMatrix();*/

    glPushMatrix();
    glTranslated(3.8, 9.0, -12.25);
    glRotated(90, 0, 1, 0);
    gluCylinder(qobj, .20, .20, 12.3, 40, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.8, 9.0, -7.75);
    glRotated(90, 0, 1, 0);
    gluCylinder(qobj, .20, .20, 12.3, 40, 5);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glPushMatrix();
    glTranslated(ballX1, ballY1, ballZ1);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(ballX2, ballY2, ballZ2);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(ballX3, ballY3, ballZ3);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(ballX4, ballY4, ballZ4);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(ballX5, ballY5, ballZ5);
    glRotated(90, 1, 0, 0);
    gluSphere(qobj, 1.0, 50, 50);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

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
    if (sceneCounter == 1) {
        glBindTexture(GL_TEXTURE_2D, texture[6]);
    }
    if (sceneCounter == 2) {
        glBindTexture(GL_TEXTURE_2D, texture[5]);
    }
    if (sceneCounter == 3) {
        glBindTexture(GL_TEXTURE_2D, texture[8]);
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
    if (sceneCounter == 1) {
        glBindTexture(GL_TEXTURE_2D, texture[0]);
    }
    if (sceneCounter == 2) {
        glBindTexture(GL_TEXTURE_2D, texture[4]);
    }
    if (sceneCounter == 3) {
        glBindTexture(GL_TEXTURE_2D, texture[9]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[11]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[11]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[11]);
        }
    }
    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + .25, kingPinkZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.3, 3.25, 15, 5);
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

    glPushMatrix();
    glTranslated(kingPinkX, kingPinkY + 3.65, kingPinkZ);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 0.0, 0.7, 40, 4);
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
        glEnable(GL_TEXTURE_2D);
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[11]);
        }
    }
    glPushMatrix();
    glTranslated(QueenPinkX, QueenPinkY + .25, QueenPinkZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.3, 3.25, 15, 5);
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
        glEnable(GL_TEXTURE_2D);
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[0]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[2]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[11]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
        }
    }
    glPushMatrix();
    glTranslated(kingGreenX, kingGreenY + .25, kingGreenZ);
    glRotated(-90, 1, 0, 0);
    gluCylinder(qobj, 0.5, 0.3, 3.25, 15, 5);
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

    glPushMatrix();
    glTranslated(kingGreenX, kingGreenY + 3.65, kingGreenZ);
    glRotated(90, 1, 0, 0);
    gluDisk(qobj, 0.0, 0.7, 40, 4);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
        if (sceneCounter == 1) {
            glBindTexture(GL_TEXTURE_2D, texture[1]);
        }
        if (sceneCounter == 2) {
            glBindTexture(GL_TEXTURE_2D, texture[3]);
        }
        if (sceneCounter == 3) {
            glBindTexture(GL_TEXTURE_2D, texture[10]);
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifRed);
    glPushMatrix();
    glTranslatef(xred, yred, zred);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawBlueBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlue);
    glPushMatrix();
    glTranslatef(xblue, yblue, zblue);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawGreenBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGreen);
    glPushMatrix();
    glTranslatef(xgreen, ygreen, zgreen);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawOrangeBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOrange);
    glPushMatrix();
    glTranslatef(xorange, yorange, zorange);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawPurpleBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifPurple);
    glPushMatrix();
    glTranslatef(xpurple, ypurple, zpurple);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawBlackBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBlack);
    glPushMatrix();
    glTranslatef(xblack, yblack, zblack);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawGreyBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifGrey);
    glPushMatrix();
    glTranslatef(xgrey, ygrey, zgrey);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawDarkGreyBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifDarkGrey);
    glPushMatrix();
    glTranslatef(xdarkgrey, ydarkgrey, zdarkgrey);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawYellowBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifYellow);
    glPushMatrix();
    glTranslatef(xyellow, yyellow, zyellow);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawBrownBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifBrown);
    glPushMatrix();
    glTranslatef(xbrown, ybrown, zbrown);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
}

void drawWhiteBox()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifWhite);
    glPushMatrix();
    glTranslatef(xwhite, ywhite, zwhite);
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
    drawWalls();
    drawClockRest();
    drawClocks();
    drawClocks2();
    drawCoffeeCup();
    drawNewtonsCraddle();
    drawLamp();
    

    //drawRedBox();
    //drawBlueBox();
    //drawGreenBox();
    //drawOrangeBox();
    //drawPurpleBox();
    //drawBlackBox();
    //drawGreyBox();
    //drawYellowBox();
    //drawBrownBox();
    //drawWhiteBox();
    //drawDarkGreyBox();

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
    
    NewtonAnimation(1);

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
    glClearColor(0.5215686274509804, 0.6980392156862745, 0.8980392156862745, 0.0);
    
    //Create texture index array.
    glGenTextures(15, texture);

    //Load external textures.
    loadExternalTextures();

    //Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_DEPTH_TEST);

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
    float lightPos0[] = { -45.0, 5, -20.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT0);

    //Light1 - Sun
    float spotAngle1 = 35;
    float spotExponent1 = 3.0;
    float lightAmb1[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos1[] = { -45, 5, -20.0, 1.0 };
    float spotDirection1[] = { -1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);

    //Light2 - Spotlight
    float spotAngle2 = 25;
    float spotExponent2 = 5.0;
    float lightAmb2[] = { 0.9, 0.9, 0.9, 1.0 };
    float lightDifAndSpec2[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos2[] = { 15, 5, -20.0, 1.0 };
    float spotDirection2[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpec2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpec2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotAngle2);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection2);
    glEnable(GL_LIGHT2);
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
        if (turnCounter < 3) {
            sceneCounter++;
            cout << "Turn counter: " << turnCounter << endl;
        }
        break;

    case 't':
        turnCounter++;
        cout << "Turn Number: " << turnCounter << endl;
        break;

    case 'n':
        newtonAnimate = !newtonAnimate;
        cout << "Newtons Craddle Switched" << endl;
        break;

    case 's':
        sun = !sun;
        if (sun) {
            glEnable(GL_LIGHT1);
        }
        else {
            glDisable(GL_LIGHT1);
        }
        break;

    case 'l':
        lamp = !lamp;
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
    if (button == GLUT_LEFT && state == GLUT_DOWN) //mouse clicked
    {
        std::cout << "left button pressed" << std::endl;
        selecting = true;
        xMouse = x;
        yMouse = height - y;

        //conversion factors
        double fw = 30.0 / width;
        double fh = -30.0 / height;

        double a = x * fw;
        double b = (height - y) * fh;

        //window coordinates
        double xW = fpX2 + -15 + a;
        double zW = fpZ2 + b;

        cout << "xW=" << xW << ' ' << "zW=" << zW << endl;
        cout << "xred=" << xred << ' ' << "zred=" << zred << endl;
        
        if (xW <= xred + 1 && xW >= xred - 1 && zW <= zred + 2.5 && zW >= zred - 2.5
            || xW <= xblue + 1 && xW >= xblue - 1 && zW <= zblue + 2.5 && zW >= zblue - 2.5
            || xW <= xgreen + 1 && xW >= xgreen - 1 && zW <= zgreen + 2.5 && zW >= zgreen - 2.5
            || xW <= xorange + 1 && xW >= xorange - 1 && zW <= zorange + 2.5 && zW >= zorange - 2.5
            || xW <= xpurple + 1 && xW >= xpurple - 1 && zW <= zpurple + 2.5 && zW >= zpurple - 2.5
            || xW <= xblack + 1 && xW >= xblack - 1 && zW <= zblack + 2.5 && zW >= zblack - 2.5
            || xW <= xgrey + 1 && xW >= xgrey - 1 && zW <= zgrey + 2.5 && zW >= zgrey - 2.5
            || xW <= xdarkgrey + 1 && xW >= xdarkgrey - 1 && zW <= zdarkgrey + 2.5 && zW >= zdarkgrey - 2.5
            || xW <= xyellow + 1 && xW >= xyellow - 1 && zW <= zyellow + 2.5 && zW >= zyellow - 2.5
            || xW <= xbrown + 1 && xW >= xbrown - 1 && zW <= zbrown + 2.5 && zW >= zbrown - 2.5
            || xW <= xwhite + 1 && xW >= xwhite - 1 && zW <= zwhite + 2.5 && zW >= zwhite - 2.5)
        {
            dragging = true;
            std::cout << "dragging" << std::endl;
        }
        else {
            dragging = false;
        }
        glutPostRedisplay();
    }

    if (button == GLUT_LEFT && state == GLUT_UP) {
        selecting = false;
        itemID = 0;
        dragging = false;
    } 

}

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

        if (itemID == PAWNPINK1) {
            xred = xW;
            zred = zW - 15.5;
            pawnPinkX1 = xred;
            pawnPinkZ1 = zred;
        }

        if (itemID == PAWNPINK2) {
            xblue = xW;
            zblue = zW - 15.5;
            pawnPinkX2 = xblue;
            pawnPinkZ2 = zblue;
        }

        if (itemID == ROOKPINK1) {
            xgreen = xW;
            zgreen = zW - 15.5;
            rookPinkX1 = xgreen;
            rookPinkZ1 = zgreen;
        }

        if (itemID == KINGPINK) {
            xorange = xW;
            zorange = zW - 15.5;
            kingPinkX = xorange;
            kingPinkZ = zorange;
        }

        if (itemID == QUEENPINK) {
            xpurple = xW;
            zpurple = zW - 15.5;
            QueenPinkX = xpurple;
            QueenPinkZ = zpurple;
        }

        if (itemID == KINGGREEN) {
            xblack = xW;
            zblack = zW - 15.5;
            kingGreenX = xblack;
            kingGreenZ = zblack;
        }

        if (itemID == ROOKGREEN1) {
            xgrey = xW;
            zgrey = zW - 15.5;
            rookGreenX1 = xgrey;
            rookGreenZ1 = zgrey;
        }

        if (itemID == ROOKGREEN2) {
            xdarkgrey = xW;
            zdarkgrey = zW - 15.5;
            rookGreenX2 = xdarkgrey;
            rookGreenZ2 = zdarkgrey;
        }

        if (itemID == PAWNGREEN1) {
            xyellow = xW;
            zyellow = zW - 15.5;
            pawnGreenX1 = xyellow;
            pawnGreenZ1 = zyellow;
        }

        if (itemID == PAWNGREEN2) {
            xbrown = xW;
            zbrown = zW - 15.5;
            pawnGreenX2 = xbrown;
            pawnGreenZ2 = zbrown;
        }

        if (itemID == BISHOPGREEN1) {
            xwhite = xW;
            zwhite = zW - 15.5;
            bishopGreenX1 = xwhite;
            bishopGreenZ1 = zwhite;
        }

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

