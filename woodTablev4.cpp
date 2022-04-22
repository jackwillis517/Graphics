//woodTablev4.cpp
//Modified from code from Hill and Kelley
//"Computer Graphics Using OpenGl" 3rd edition
//table with wooden top.
//Reads in two textures, wood and grass
//Uses only one at first


#include <cstdlib>
#include <iostream>
#include <fstream>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//globals
GLuint mywood;
int wrap=1;
//int wrap=0;
static unsigned int texture[2]; // Array of texture indices.


// Struct of bitmap file.
struct BitMapFile
{
  int sizeX;
  int sizeY;
  unsigned char *data;
};

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile *getBMPData(string filename)
{
    BitMapFile *bmp = new BitMapFile;
    unsigned int size, offset, headerSize;
    
    // Read input file name.
    ifstream infile(filename.c_str(), ios::binary);
    
    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char *) &offset, 4);
    
    // Get the header size of the bitmap.
    infile.read((char *) &headerSize,4);
    
    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read( (char *) &bmp->sizeX, 4);
    infile.read( (char *) &bmp->sizeY, 4);
    
    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    cout << size << endl;
    bmp->data = new unsigned char[size];
    
    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char *) bmp->data , size);
    
    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i+2];
        bmp->data[i+2] = temp;
    }
    
    return bmp;
}

// Load external textures.
void loadExternalTextures()			
{
  // Local storage for bmp image data.
  BitMapFile *image[2];
  
  // Load the textures.
  //first texture
  image[0] = getBMPData("Textures/cherrywood.bmp");
  
  // Bind wood image to texture index[0]. 
  glBindTexture(GL_TEXTURE_2D, texture[0]); 
  // if wrap is true, the texture repeats, ignoring integer part 
  //	... false, the texture does not go beyond 1.
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP ); 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
  
  // select modulate to mix texture with color for shading 
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  
  // when texture area is small, bilinear filter the closest mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );   
  // when texture area is large, bilinear filter the first mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  // when texture area is small, bilinear filter the closest mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );   
  // when texture area is large, bilinear filter the first mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0, 
               GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
  
  // build our texture mipmaps 
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image[0]->sizeX, image[0]->sizeY,GL_RGB, GL_UNSIGNED_BYTE, image[0]->data );
  
  
  //second texture
  image[1] = getBMPData("Textures/smallgrass.bmp");
  
  // Bind smallgrass image to texture index[1]. 
  glBindTexture(GL_TEXTURE_2D, texture[1]); 
  // if wrap is true, the texture repeats, ignoring integer part 
  //	... false, the texture does not go beyond 1.
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP ); 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
  
  // select modulate to mix texture with color for shading 
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  
  // when texture area is small, bilinear filter the closest mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );   
  // when texture area is large, bilinear filter the first mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  // when texture area is small, bilinear filter the closest mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );   
  // when texture area is large, bilinear filter the first mipmap 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0, 
               GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
  
  // build our texture mipmaps 
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image[1]->sizeX, image[1]->sizeY,GL_RGB, GL_UNSIGNED_BYTE, image[1]->data );
  
  
}



//glut solid cube doesn't have texture.
//Here is the source code for a textured cube modified from
//http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06
//The comments next to a line were for applying the whole texture patch.
//I have comments above two of the edges, just applying a strip of wood.
//Notice I have not nicely textured the hidden edges.

void woodenCube(double side)
{
  
 glBindTexture(GL_TEXTURE_2D, texture[0]);
glBegin(GL_QUADS);
    
// Front Face
  //Modified the way to apply the texture, to be just a strip of wood.
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
glTexCoord2f(1.0f, .15f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
glTexCoord2f(0.0f, .15f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
// Back Face
    
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
 
   // Bottom Face
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
// Right face

  //Modified the way to apply the texture, to be just a strip of wood.
glTexCoord2f(.7f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
glTexCoord2f(.8f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
glTexCoord2f(.8f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
glTexCoord2f(.7f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
// Left Face

glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
glEnd();
  
  

glBegin(GL_QUADS);
// Top Face

glTexCoord2f(0.0f, 6.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
glTexCoord2f(6.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
glTexCoord2f(6.0f, 6.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
glEnd();
}

void tableLeg(double thick,double len)
{
  glPushMatrix();
  glTranslated(0.0, len/2, 0.0);
  glScaled(thick,len,thick);
  glutSolidCube(1.0);
  glPopMatrix();
}

//draw the table - a top and four legs
void table(double topWid, double topThick, double legThick, double legLen)
{
  double dist = 0.95*topWid/2-legThick/2.0;
  
  glPushMatrix();
  glTranslated(0, legLen,0);
  glScaled(topWid, topThick, topWid);
  glEnable(GL_TEXTURE_2D);
  // Create texture index array.
  glGenTextures(2, texture);
  //set up table top texture 
  loadExternalTextures();
  woodenCube(1.0);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glPushMatrix();
  glTranslated(dist,0,dist);
  tableLeg(legThick,legLen);
  glTranslated(0,0, -2*dist);
  tableLeg(legThick,legLen);
  glTranslated(-2*dist, 0,2*dist);
  tableLeg(legThick,legLen);
  glTranslated(0,0, -2*dist);
  tableLeg(legThick,legLen);
  glPopMatrix();  
}

void mydisplay()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen
  //Set material properties
  //GLfloat mat_ambient[]={ .7f, .7f, .7f,1.0f} ;//gray
  GLfloat mat_ambient[]={ 6.0f, 6.0f, 6.0f,1.0f} ;
  //GLfloat mat_diffuse[]={ .6f, .6f, .6f,1.0f};
  GLfloat mat_diffuse[]={ 1.f, 1.f, 1.f,1.0f};
  GLfloat mat_specular[]={ 1.0f, 1.0f, 1.0f,1.0f};
  GLfloat mat_shininess[]={50.0f};
  //set the light properties
  GLfloat lightIntensity[]={.7f,.7f,.7f,1.0f};
  GLfloat light_position[]={12.0f, 6.0f, 3.0f, 0.0f};
  
  double winHt=1.0;  //half height of the window
  
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  
  glLightfv(GL_LIGHT0,GL_POSITION, light_position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE, lightIntensity);
  
  
  //set the camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //try distance and close up - gluLookAt not affected.
  //glOrtho(-2, 2.0, -2, 2, 0.1,10.0);
  glOrtho(-winHt*64/48.0/2, winHt*64/48.0/2, -winHt/2, winHt/2, 0.1,100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2.3, 1.3, 2,   0,.25,0,   0.0, 1.0, 0.0);
  
  table(.6, .02,.02,.3);
  
  glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main( int argc, char **argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("shaded example -3D scene");
  //glutDisplayFunc(displaySolid);
  glutDisplayFunc(mydisplay);
  glutKeyboardFunc(keyInput);
  
  glEnable(GL_LIGHTING);  //enable the light source
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST); // for removal of hidden surfaces
  glEnable(GL_NORMALIZE);  // normalize vectors for proper shading
  glClearColor(0.8f, 0.8f, 0.8f,0.0f);  // background is light gray
  glViewport(0, 0, 640, 480);
  glutMainLoop();
  return 0;
}
