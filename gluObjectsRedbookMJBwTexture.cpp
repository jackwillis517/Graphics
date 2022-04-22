//from the redbook gluObjectsRedbook.cpp
//http://www.glprogramming.com/red/chapter11.html
//with texture code from fieldAndSky.cpp added.
//And: gluQuadricTexture
//And: change to modulate for light to show through.
//Mixture done by Marjory Baruch

#include <iostream>
#include <fstream>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;  //need for string

static unsigned int texture[3]; // Array of texture indices.

GLuint startList;

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
    image[0] = getBMPData("Textures/cherrywood.bmp");
    image[1] = getBMPData("Textures/cherrywood.bmp");
    
    // Bind grass image to texture index[0].
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); //MJB
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); //MJB
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
    
    // Bind sky image to texture index[1]
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
}

void errorCallback(GLenum errorCode)
{
  const GLubyte *estring;
  
  estring = gluErrorString(errorCode);
  fprintf(stderr, "Quadric Error: %s\n", estring);
  exit(0);
}

void init(void) 
{
    // Create texture index array.
    glGenTextures(3, texture);
    
    // Load external textures.
    loadExternalTextures();
    
    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
    
    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    
  GLUquadricObj *qobj;
  GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  
  /* Create 4 display lists, each with a different quadric object.
   * Different drawing styles and surface normal specifications
   * are demonstrated.
   */
  startList = glGenLists(4);
  qobj = gluNewQuadric();
  //gluQuadricCallback(qobj, GLU_ERROR, errorCallback);
  
  gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
  gluQuadricNormals(qobj, GLU_SMOOTH);
  gluQuadricTexture(qobj,true);
  glNewList(startList, GL_COMPILE);
  gluSphere(qobj, 0.75, 15, 10);
  glEndList();
  
  //  glEnable(GL_NORMALIZE);
  gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
  gluQuadricNormals(qobj, GLU_FLAT);
  glNewList(startList+1, GL_COMPILE);
   // glPushMatrix();
    //glScaled(2, 2, 2);
  gluCylinder(qobj, 0.5, 0.3, 1.0, 15, 5);
   // glPopMatrix();
  glEndList();
  
  gluQuadricDrawStyle(qobj, GLU_LINE); /* wireframe */
  gluQuadricNormals(qobj, GLU_NONE);
  glNewList(startList+2, GL_COMPILE);
  gluDisk(qobj, 0.25, 1.0, 20, 4);
  glEndList();
  
  gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
  gluQuadricNormals(qobj, GLU_NONE);
  glNewList(startList+3, GL_COMPILE);
  gluPartialDisk(qobj, 0.0, 1.0, 20, 4, 0.0, 225.0);
  glEndList();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glEnable(GL_LIGHTING);
  glShadeModel (GL_SMOOTH);
  glTranslatef(-1.0, -1.0, 0.0);
  glCallList(startList);
  
  glShadeModel (GL_FLAT);
  glTranslatef(0.0, 2.0, 0.0);
  glPushMatrix();
  glRotatef(300.0, 1.0, 0.0, 0.0);
  glCallList(startList+1);
  glPopMatrix();
  
  glDisable(GL_LIGHTING);
  glColor3f(0.0, 1.0, 1.0);
  glTranslatef(2.0, -2.0, 0.0);
  glCallList(startList+2);
  
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef(0.0, 2.0, 0.0);
  glCallList(startList+3);
  
  glPopMatrix();
  glFlush();
}

void reshape (int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
            2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
  else
    glOrtho(-2.5*(GLfloat)w/(GLfloat)h,
            2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500); 
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
