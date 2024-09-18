
//Project 2:  Modeling Transformations

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>
using namespace std;
float Wwidth,Wheight;
bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */

static void resize(int width, int height)
{
      double Ratio;

     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 }

float sphererotation = 0.0;     //rotation angle declaration for sphere
float teapotrotation = 0.0;     //rotation angle declaration for teapot
float cuberotation = 0.0;       //rotation angle declaration for cube

float zsphere = 0.0;   //z co-ordinate for sphere to move back and forth
float zteapot = 0.0;   //z co-ordinate for teapot to move back and forth
float zcube = 0.0;     //z co-ordinate for cube to move back and forth


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here
    glPushMatrix();    //saves current matrix
    glColor3f(0.0,0.0,1.0);  //setting sphere color to blue
    //setting coordinates for sphere, with x and y already assigned, z will keep on changing as per the user - to move back and forth
    glTranslatef(-4.0,0.0,zsphere);
    glRotatef(sphererotation,0.0,1.0,0.0);    //rotating sphere around y-axis
    glutSolidSphere(1.0,20,20);   //setting sphere radius = 1 and slices and stacks = 20
    glPopMatrix();  //restores previous matrix

    glPushMatrix();   //saves current matrix
    glColor3f(1.0,0.0,0.0);   //setting teapot color to red
    //setting coordinates for teapot, with x and y already assigned, z will keep on changing as per the user - to move back and forth
    glTranslatef(0.0,0.0,zteapot);
    glRotatef(teapotrotation,0.0,1.0,0.0);   //rotating teapot around y-axis
    glutSolidTeapot(1.3);  //setting teapot size to 1.3
    glPopMatrix();   //restores previous matrix

    glPushMatrix();   //saves current matrix
    glColor3f(0.0,1.0,0.0);   //setting cube color to green
    //setting coordinates for sphere, with x and y already assigned, z will keep on changing as per the user - to move back and forth
    glTranslatef(4.0,0.0,zcube);
    glRotatef(cuberotation,0.0,1.0,0.0);    //rotating cube around y-axis
    glutSolidCube(1.5);   //setting cube size of 1.5
    glPopMatrix();   //restores previous matrix


    glutSwapBuffers();
}

//creating three flags each for sphere, teapot and cube
//so that each shape can be scaled and rotated separately

bool flagTeapot = 0;    //flag for teapot
bool flagCube = 0;      //flag for cube
bool flagSphere = 0;    //flag for sphere
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 't':      //if t is pressed, flag for teapot = 1, all the other flags sets to 0
            flagTeapot = 1;
            flagCube = 0;
            flagSphere = 0;
            break;
        case 'c':     //if c is pressed, flag for cube = 1, all the other flags sets to 0
            flagCube = 1;
            flagTeapot = 0;
            flagSphere = 0;
            break;
        case 's':    //if s is pressed, flag for sphere = 1, all the other flags sets to 0
            flagSphere = 1;
            flagCube = 0;
            flagTeapot = 0;
            break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
        // Create 3 flags as 1 2 3, when 1 is 1 other are 0

        case GLUT_KEY_UP:  //keyboard up_key is pressed
        if(flagTeapot){    //when true i.e. when t is pressed
            zteapot += 0.5;    //teapot moves forward
        }
        if(flagCube){    //when true i.e. when c is pressed
            zcube += 0.5;   //cube moves forward
        }
        if(flagSphere){   //when true i.e. when s is pressed
            zsphere += 0.5;  //sphere moves forward
        }
        break;
        case GLUT_KEY_DOWN:  //keyboard down_key is pressed
            if(flagTeapot){   //when true
            zteapot -= 0.5;   //teapot moves backward
        }
        if(flagCube){   //when true
            zcube -= 0.5;   //cube moves backward
        }
        if(flagSphere){   //when true
            zsphere -= 0.5;   //sphere moves backward
        }
        break;

        case GLUT_KEY_LEFT:   //keyboard left_key is pressed
            if(flagTeapot){   //when true
            teapotrotation += 5.0;  //teapot rotates with 5 degrees increment
        }
        if(flagCube){      //when true
            cuberotation += 5.0;   //cube rotates with 5 degree increment
        }
        if(flagSphere){    //when true
            sphererotation += 5.0;   //sphere rotates with 5 degrees increment
        }
        break;
        case GLUT_KEY_RIGHT:   //keyboard right_key is pressed
            if(flagTeapot){   //when true
            teapotrotation -= 5.0;  //teapot rotates with 5 degrees decrement
        }
        if(flagCube){    //when true
            cuberotation -= 5.0;   //cube rotates with 5 degrees decrement
        }
        if(flagSphere){   //when true
            sphererotation -= 5.0;   //sphere rotates with 5 degrees decrement
        }

        break;
   }
  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1000,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
