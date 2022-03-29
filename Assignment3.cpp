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
* References: None
*
* Interactions:   
*   Press f to fly around
    Press o to power on/off propellers
    Press left mouse button on helicopter to drop a balloon
    Press down arrow to drop a balloon
    Press 1, 2, 3, 4, 0 to change view
    Press r to reset view"
    Press left/right arrow to decrease/increase speed

    ////////////////////////////////////////////////////////////////////////////////////////////////
    README: In order for color picking to work for the second balloon to drop, select anything other 
    then the helicopter when you see "SELECTED!" and reselect the helicopter. <------------------
    ///////////////////////////////////////////////////////////////////////////////////////////////
*******************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


using namespace std;
static int PI = 3.14159;
static int frustrumWindow;
static bool overhead = false;
static int score = 0;
static int clicked = 0;
static bool scored1 = false;
static bool scored2 = false;
static bool balloon1HitGround = false;
static bool balloon2HitGround = false;
static float balloon1HitGroundX = 0.0;
static float balloon1HitGroundZ = 0.0;
static float balloon2HitGroundX = 0.0;
static float balloon2HitGroundZ = 0.0;

//Color picking, mouse & perspective globals
static int HELI = 1;
static int TORUS = 2;
static int itemID = 0;
static int xMouse, yMouse;
static int height, width;
static bool selecting = false;
static int lookPos = 0;

//Helicopter globals
static int propRot = 0;
static int act = 1;
static float heliSpeed = .0003;
static bool heliPower = false;
static bool heliAnimate = false;
static bool balloonAnimate = false;
static bool balloonAnimate2 = false;

//Position globals
static float xPosHeli = 0;
static float yPosHeli = 0;
static float zPosHeli = 0;
static float xPosBalloon1 = 6;
static float yPosBalloon1 = 1;
static float zPosBalloon1 = -6;
static float xPosBalloon2 = 6;
static float yPosBalloon2 = 1;
static float zPosBalloon2 = -7;

//Color rgbs for objects
static float cone1ColorR = 0.0;
static float cone1ColorG = 1.0;
static float cone1ColorB = 0.0;
static float cone2ColorR = 0.76862745098039215686274509803922;
static float cone2ColorG = 0.21568627450980392156862745098039;
static float cone2ColorB = 0.86666666666666666666666666666667;
static float cone3ColorR = 0.0;
static float cone3ColorG = 1.0;
static float cone3ColorB = 1.0;
static float treeColorR = 0.0;
static float treeColorG = 1.0;
static float treeColorB = 0.0;
static float carBodyColorR = 0.0;
static float carBodyColorG = 1.0;
static float carBodyColorB = 0.0;


//---------------------------------------------Utility Functions------------------------------------------------//
//Projection for entire project
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (overhead) {
        glOrtho(-4, 4, -4, 4, 1, 21);
    }
    else {
        glFrustum(-4, 4, -4, 4, 1, 21);
    }
    glMatrixMode(GL_MODELVIEW);
}

//Identification function for color picking
void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0) {
        itemID = HELI;
        clicked++;
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
    if (xPosHeli >= -8 && xPosHeli <= -2 && zPosHeli >= -4 && zPosHeli <= 5 && yPosBalloon1 < -5 && yPosBalloon1 > -30) {
        cone1ColorR = 0.0;
        cone1ColorG = 0.0;
        cone1ColorB = 1.0;
        cone2ColorR = 0.0;
        cone2ColorG = 0.0;
        cone2ColorB = 1.0;
        cone3ColorR = 0.0;
        cone3ColorG = 0.0;
        cone3ColorB = 1.0;
        if (!scored1) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored1 = true;
        }
    } else if (xPosHeli >= 9 && xPosHeli <= 12 && zPosHeli >= -7 && zPosHeli <= -3 && yPosBalloon1 < -5 && yPosBalloon1 > -30) {
        treeColorR = 0.0;
        treeColorG = 0.0;
        treeColorB = 1.0;
        if (!scored1) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored1 = true;
        }
    } else if (xPosHeli >= 9 && xPosHeli <= 12 && zPosHeli >= 1 && zPosHeli <= 6 && yPosBalloon1 < -5 && yPosBalloon1 > -30) {
        if (!scored1) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored1 = true;
        }
    }
    else {
        if (yPosBalloon1 < -5 && yPosBalloon1 > -30 && !balloon1HitGround) {
            balloon1HitGround = true;
            balloon1HitGroundX = xPosHeli;
            balloon1HitGroundZ = zPosHeli;
        }
    }

    if (xPosHeli >= -8 && xPosHeli <= -2 && zPosHeli >= -4 && zPosHeli <= 5 && yPosBalloon2 < -5 && yPosBalloon2 > -30) {
        cone1ColorR = 1.0;
        cone1ColorG = 0.0;
        cone1ColorB = 0.0;
        cone2ColorR = 1.0;
        cone2ColorG = 0.0;
        cone2ColorB = 0.0;
        cone3ColorR = 1.0;
        cone3ColorG = 0.0;
        cone3ColorB = 0.0;
        if (!scored2) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored2 = true;
        }
    }else if (xPosHeli >= 9 && xPosHeli <= 12 && zPosHeli >= -7 && zPosHeli <= -3 && yPosBalloon2 < -5 && yPosBalloon2 > -30) {
        treeColorR = 1.0;
        treeColorG = 0.0;
        treeColorB = 0.0;
        if (!scored2) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored2 = true;
        }
    }else if (xPosHeli >= 9 && xPosHeli <= 12 && zPosHeli >= 1 && zPosHeli <= 6 && yPosBalloon2 < -5 && yPosBalloon2 > -30) {
        carBodyColorR = 1.0;
        carBodyColorG = 0.0;
        carBodyColorB = 0.0;
        if (!scored2) {
            score += 1;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "-------------------------------------------" << endl;
            scored2 = true;
        }
    }
    else {
        if (yPosBalloon1 < -5 && yPosBalloon1 > -30 && !balloon2HitGround) {
            balloon2HitGround = true;
            balloon2HitGroundX = xPosHeli;
            balloon2HitGroundZ = zPosHeli;
        }
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
    if (yPosBalloon1 > -35) {
        yPosBalloon1 -= .005;
    }
    glutPostRedisplay();
}

void balloonAnimation(int x) 
{
    if (balloonAnimate) animateBalloon();
    glutTimerFunc(100, balloonAnimation, 1);
}

void animateBalloon2()
{
    if (yPosBalloon2 > -35) {
        yPosBalloon2 -= .005;
    }
    glutPostRedisplay();
}

void balloonAnimation2(int x)
{
    if (balloonAnimate2) animateBalloon2();
    glutTimerFunc(100, balloonAnimation2, 1);
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

    glColor3f(1.0, 0, 0.0);
    glPushMatrix();
    glTranslated(xPosBalloon2, yPosBalloon2, zPosBalloon2);
    glScaled(.5, .5, .5);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
}

void drawHeli(float c1, float c2, float c3, int isShadow)
{
    //Helicopter Body
    glColor3f(c1, c2, c3);
    glPushMatrix();
    if (isShadow) {
        glTranslated(6, 0, -6);
        glScaled(2, 0, 3);
    }
    else {
        glTranslated(6, 3, -6);
        glScaled(2, 2, 3);
    }
    glutSolidSphere(1, 25, 25);
    glPopMatrix();

    drawBalloons();

    //Helicopter Tail
    glPushMatrix(); 
    if (isShadow) {
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(6, 0, -12);
        glScaled(.5, 0, 10);
    }
    else {
        glColor3f(0.0, 1.0, 0.0);
        glTranslated(6, 3, -12);
        glScaled(.5, .5, 10);
    }
    glutSolidCube(1);
    glPopMatrix();

    //Helicopter Prop
    glPushMatrix();
    if (isShadow) {
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(6, 0, -6);
        glRotated(propRot, 0, 1, 0);
        glScaled(.25, 0, 10);
    }
    else {
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(6, 5, -6);
        glRotated(propRot, 0, 1, 0);
        glScaled(.25, .25, 10);
    }
    glutSolidCube(1);
    glPopMatrix();

    //Helicopter Tail Props
    glPushMatrix();
    if (isShadow) {
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(6.25, 0, -17);
        glRotated(propRot, 1, 0, 0);
        glRotated(90, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        glScaled(.15, 0, 3);
    }
    else {
        glColor3f(0.0, 0.0, 1.0);
        glTranslated(6.25, 3, -17);
        glRotated(propRot, 1, 0, 0);
        glRotated(90, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        glScaled(.15, .15, 3);
    }
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    if (isShadow) {
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(6.25, 0, -17);
        glRotated(propRot, 1, 0, 0);
        glRotated(90, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        glScaled(.15, 0, 3);
    }
    else {
        glColor3f(0.0, 0.0, 1.0);
        glTranslated(6.25, 3, -17);
        glRotated(propRot, 1, 0, 0);
        glRotated(90, 0, 1, 0);
        glRotated(90, 0, 1, 0);
        glScaled(.15, .15, 3);
    }
    glutSolidCube(1);
    glPopMatrix();

    if (!isShadow){
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
    glColor3f(carBodyColorR, carBodyColorG, carBodyColorB);
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
    
    glColor3f(treeColorR, treeColorG, treeColorB);
    glPushMatrix();
    glTranslated(12, 5, -17);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
}

void drawHoop(float c1, float c2, float c3)
{
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(-3, 2, -10);
    glScaled(.25, 25, .5);
    glutSolidCube(1);
    glPopMatrix();

    //Pink torus
    glColor3f(c1, c2, c3);
    glPushMatrix();
    glTranslated(-3, 21, -10);
    glutWireTorus(1, 6, 30, 30);
    glPopMatrix();
}

void drawPaintBlueSpot(float x, float y, float z) {
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidCube(1);
    glPopMatrix();
}

void drawPaintRedSpot(float x, float y, float z) {
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidCube(1);
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
    glTranslated(xPosHeli, yPosHeli, zPosHeli);
    if (itemID == HELI && clicked == 1)
    {
        drawClickedText();
        balloonAnimate = true;
    }
    if (itemID == HELI && clicked == 2)
    {
        drawClickedText();
        balloonAnimate2 = true;
    }
    if (selecting)
    {
        glDisable(GL_DEPTH_TEST);
            glPushMatrix();
            drawHeli(0.0, 0.0, 0.0, 1);
            glPopMatrix();
        glEnable(GL_DEPTH_TEST);
        drawHeli(1.0, 0.0, 0.0, 0);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
            glPushMatrix();
            drawHeli(0.0, 0.0, 0.0, 1);
            glPopMatrix();
        glEnable(GL_DEPTH_TEST);
        drawHeli(0.94901960784313725490196078431373, 0.42352941176470588235294117647059, 0.07450980392156862745098039215686, 0);
    }
    glPopMatrix();

    propAnimation();
    
    heliAnimation(1);
    
    balloonAnimation(1);
  
    balloonAnimation2(1);
    
    checkCollision();

    if (balloon1HitGround) {
        drawPaintBlueSpot(balloon1HitGroundX, -.25, balloon1HitGroundZ);
    }

    if (balloon2HitGround) {
        drawPaintRedSpot(balloon2HitGroundX, -.25, balloon2HitGroundZ);
    }

    drawGround();

    glPushMatrix();
    glTranslated(0, -2, 4);
    drawCar();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -2, 2);
    drawCones();
    glPopMatrix();
   
    drawHoop(0.98823529411764705882352941176471, 0.01960784313725490196078431372549, 0.63137254901960784313725490196078);
   
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

    //Overhead
    if (lookPos == 4) {
        gluLookAt(6, 21, -6,
            6, -5, -6,
            0, 0, -1);
        glutPostRedisplay();
    }

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
        overhead = false;
        break;

    case '2':
        lookPos = 1;
        overhead = false;
        break;

    case '1':
        lookPos = 2;
        overhead = false;
        break;

    case '4':
        lookPos = 3;
        overhead = false;
        break;

    case 'o':
        heliPower = !heliPower;
        break;

    case 'f':
        heliAnimate = !heliAnimate;
        break;

    case '0':
        lookPos = 4;
        overhead = true;
        break;

    case 'r':
        overhead = false;
        score = 0;
        scored1 = false;
        scored2 = false;
        clicked = 0;
        itemID = 0;
        selecting = false;
        lookPos = 0;
        propRot = 0;
        act = 1;
        heliSpeed = .0003;
        heliPower = false;
        heliAnimate = false;
        balloonAnimate = false;
        balloonAnimate2 = false;
        balloon1HitGround = false;
        balloon2HitGround = false;
        balloon1HitGroundX = 0.0;
        balloon1HitGroundZ = 0.0;
        balloon2HitGroundX = 0.0;
        balloon2HitGroundZ = 0.0;
        xPosHeli = 0;
        yPosHeli = 0;
        zPosHeli = 0;
        xPosBalloon1 = 6;
        yPosBalloon1 = 1;
        zPosBalloon1 = -6;
        xPosBalloon2 = 6;
        yPosBalloon2 = 1;
        zPosBalloon2 = -7;
        cone1ColorR = 0.0;
        cone1ColorG = 1.0;
        cone1ColorB = 0.0;
        cone2ColorR = 0.76862745098039215686274509803922;
        cone2ColorG = 0.21568627450980392156862745098039;
        cone2ColorB = 0.86666666666666666666666666666667;
        cone3ColorR = 0.0;
        cone3ColorG = 1.0;
        cone3ColorB = 1.0;
        treeColorR = 0.0;
        treeColorG = 1.0;
        treeColorB = 0.0;
        carBodyColorR = 0.0;
        carBodyColorG = 1.0;
        carBodyColorB = 0.0;

    default:
        break;
    }
}

void keyInputSpecial(int key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case GLUT_KEY_DOWN:
        itemID = HELI;
        clicked++;
        break;

    case GLUT_KEY_RIGHT:
        heliSpeed += .00005;
        break;

    case GLUT_KEY_LEFT:
        heliSpeed -= .00005;
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
    cout << "Press f to fly around" << endl;
    cout << "Press o to power on/off propellers" << endl;
    cout << "Press left mouse button on helicopter to drop a balloon" << endl;
    cout << "Press down arrow to drop a balloon" << endl;
    cout << "Press 1, 2, 3, 4, 0 to change view" << endl;
    cout << "Press r to reset view" << endl;
    cout << "Press left/right arrow to decrease/increase speed" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "--------------" << "SCORE: " << score << "---------------------" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "-------------------------------------------" << endl;

}

//Main Loop
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    frustrumWindow = glutCreateWindow("Helicopter Bloon Dropper");
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

