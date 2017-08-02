#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float xt = 1.0, yt = 1.0;            // Keyboard Interactives
float x = 1.0,y = 1.0,z=1.0;    // Movement of the fish
float angle =0;  				// Function animation
float autorun = 300;			// Movement autorun
float autoDec = 0.05;

GLfloat light_position[] = {0.0f, 0.0f, 50.0f, 0.0f}; // Position of light
GLfloat diffuse_light[] = {0.0f, 0.0f, 0.0f, 0.0f}; // Position of the diffuse light
GLfloat green[] = {0.0f,1.0f,0.0f}; // Colour for green
float pyScaleX = 0.35; // Scale factor X for pyramid
float pyScaleY = 0.2; // Scale factor Y for pyramid
float pyScaleZ = 0.2; // Scale factor Z for pyramid
float cubeSX = 0.5, cubeSY = 0.5, cubeSZ = 0.5; // Scale factor for X, Y, Z for the cube
float xSp = 0.3, ySp = 0.3, zSp = 0.3; // Scale factor X, Y, Z for the sphere
float xRot = 0, yRot = 0, xFRot = 0, yFRot = 0; // Rotation factor X and Y for the fish and the other objects.

void animation(void) // Animates for the fish to wag its tail.
{
	if(angle>=0 && angle<10)
		angle = angle+0.5;
	else angle = 0;
	glutPostRedisplay();
}
void Auto(void) // Allows for automatic running of the fish from one side of the screen to another.
{
	if(autorun<=300 && autorun>-350)
		autorun = autorun-autoDec;
	else autorun = 300;
	glutPostRedisplay();
}
void settings(void) // Settings for the initial display screen
{
	glClearColor(0.0,0.0,0.0,0.0);
	glPointSize(5.0);
	glLineWidth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,400.0,0.0,400.0);
}

void doLights() // Activation of light sources
{
	glEnable (GL_FOG);
	glEnable (GL_LIGHT0);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse_light);
}

void drawCube() // Draws the cube with certain colors on each side of the polygon
{
	glLoadIdentity();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glScalef(cubeSX, cubeSY, cubeSZ);
	glRotatef(xRot,0.0 , 1.0, 1.0);
	glRotatef(yRot,1.0 , 0.0, 1.0);
	glTranslatef(-1,0,0);
	
	glMaterialfv(GL_POLYGON, GL_AMBIENT, green);
	glMaterialfv(GL_POLYGON, GL_SPECULAR, green);
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  1.0, 1.0 );
	glVertex3f(  0.5, -0.5, 0.5 );
	glVertex3f(  0.5,  0.5, 0.5 );
	glVertex3f( -0.5,  0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();
	
	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(  1.0,  0.0,  1.0 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5,  0.5, -0.5 );
	glVertex3f( 0.5,  0.5,  0.5 );
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();
	
	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  1.0,  0.0 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	
	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  0.0,  1.0 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
	
	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawFish() // Draws the green/red fish
{
	glPushMatrix();
	glPushMatrix();
	glRotatef(xFRot,0.0 , 1.0, 1.0);
	glRotatef(yFRot,1.0 , 0.0, 1.0);
	
	glBegin(GL_POLYGON);				// draw the body
	glColor3f(0.0,1.0,0.0);
	glVertex2i(40,200);
	glVertex2i(120,280);
	glVertex2i(320,200);
	glVertex2i(100,160);
	glEnd();
	
	glBegin(GL_POLYGON);			// draw the tail
	glColor3f(0.0,1.0,0.0);
	glVertex2i(320,200);
	glVertex2i(360,240);
	glVertex2i(340,200);
	glVertex2i(360,160);
	glVertex2i(320,200);
	glEnd();
	
	glBegin(GL_POLYGON);		 // draw the top fin
	glColor3f(1.0,0.0,0.0);
	glVertex2i(120,280);
	glVertex2i(140,300);
	glVertex2i(280,216);
	glVertex2i(120,280);
	glEnd();

	glBegin(GL_POLYGON);		 // draw the bottom fin
	glColor3f(1.0,0.0,0.0);
	glVertex2i(100,160);
	glVertex2i(140,200);
	glVertex2i(120,164);
	glVertex2i(100,160);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void drawSphere() // Draws the sphere (pearl)
{
	glLoadIdentity();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glRotatef(xRot,0.0 , 1.0, 1.0);
	glRotatef(yRot,1.0 , 0.0, 1.0);
	glScalef(xSp, ySp, zSp);
	glTranslatef(-2.5,1.5,1);
	glutSolidSphere (0.8, 30, 16);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawPyramid() // Draws the pyramid (split rock)
{
	
	glLoadIdentity();
	glPushMatrix();
	glPushMatrix();
	glScalef(pyScaleX, pyScaleY, pyScaleZ);
	glRotatef(xRot,0.0 , 1.0, 1.0);
	glRotatef(yRot,1.0 , 0.0, 1.0);
	glTranslatef(0.4,2.6,1);
	
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0f, 1.0f, 1.0f );
	glVertex3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glVertex3f( 1.0f, -1.0f, 1.0f);

	glVertex3f( 0.0f, 1.0f, 0.0f);
	glVertex3f( -1.0f, -1.0f, 1.0f);
	glVertex3f( 0.0f, -1.0f, -1.0f);

	glVertex3f( 0.0f, 1.0f, 0.0f);
	glVertex3f( 0.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);

	glVertex3f( -1.0f, -1.0f, 1.0f);
	glVertex3f( 0.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glEnd();
	
	glPopMatrix();
	glPopMatrix();
	
}

void outputKeys(float x, float y, const char *string) // Function to display the commands on the menu
{
	int length, i;

	void* text = GLUT_BITMAP_9_BY_15;
	
	length = (int) strlen(string);

	glColor3f(1.0f, 1.0f, 1.0f);
	
	glRasterPos2f(x,y);
	
	/* Loops every character of the string to output to the display */
	for(i=0; i<length; i++)
	{
		glutBitmapCharacter(text, string[i]);
	}
}

void draw(void) //  Draw function to draw all the objects in the scene
{
    drawFish();
    drawPyramid();
    drawCube();
    drawSphere();
}

void Display(void) // Displays all the things you see on the screen
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//drawPyramid();
	
	glPushMatrix();
	glPushMatrix();
	glRotatef(angle,0.0,0.0,0.0); 
	glTranslatef(autorun,0.0,0.0); 
	glTranslatef(xt,yt,0.0);
	
	draw();
	
	/* Output statement for command keys */
	outputKeys(-0.95,-0.1, "############ Commands ############");
	outputKeys(-0.95,-0.15, "Zoom: ");
	outputKeys(-0.95,-0.2, "   <Z>: Zoom In");
	outputKeys(-0.95,-0.25, "   <z>: Zoom Out");
	outputKeys(-0.95,-0.3, "Rotation:");
	outputKeys(-0.95,-0.35, "   <X>/<x>: X-axis rotation");
	outputKeys(-0.95,-0.4, "   <Y>/<y>: Y-axis rotation");
	outputKeys(-0.95,-0.45, "Animations:");
	outputKeys(-0.95,-0.5, "   <A>/<a>: Activate animation");
	outputKeys(-0.95,-0.55, "   <F>/<f>: Faster animation");
	outputKeys(-0.95,-0.6, "   <S>/<s>: Slower animation");
	outputKeys(-0.95,-0.65, "   <T>/<t>: Pause animation");
	outputKeys(-0.95,-0.7, "   <C>/<c>: Resume animation");
	outputKeys(-0.95,-0.75, "Switch Rendering:");
	outputKeys(-0.95,-0.8, "   <p> : Flat shaded polygonization");
	outputKeys(-0.95,-0.85, "   <P> : Smooth shaded polygonization"); 
	
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	
	glutSwapBuffers();
	glFlush();
}
void keyboard(GLubyte key, int x, int y)   // Keyboard commands that the user can do to the scene (i.e. rotation, zoom in/out etc.)
{
	switch ( key )
	{
	case 'z':             // Zoom out
			glScalef(0.9,0.9,0.9);
			pyScaleX = pyScaleX - 0.01;
			pyScaleY = pyScaleY - 0.01;
			pyScaleZ = pyScaleZ - 0.01;
			cubeSX = cubeSX - 0.01;
			cubeSY = cubeSY - 0.01;
			cubeSZ = cubeSZ - 0.01;
			xSp = xSp - 0.01;
			ySp = ySp - 0.01;
			zSp = zSp - 0.01;
			glutPostRedisplay();
			break;

	case 'Z':	// Zoom in
			glScalef(1.1,1.1,1.1);
			pyScaleX = pyScaleX + 0.01;
			pyScaleY = pyScaleY + 0.01;
			pyScaleZ = pyScaleZ + 0.01;
			cubeSX = cubeSX + 0.01;
			cubeSY = cubeSY + 0.01;
			cubeSZ = cubeSZ + 0.01;
			xSp = xSp + 0.01;
			ySp = ySp + 0.01;
			zSp = zSp + 0.01;
			glutPostRedisplay();
			break;

	case 'X':	// Rotate Positive X
			xRot = xRot + 0.5;
			xFRot = xFRot + 0.01;
			//glRotatef(0.01,0.0,1.0,1.0);
			glutPostRedisplay();
			break;

	case 'x':	// Rotate Negative X
			xRot = xRot - 0.5;
			xFRot = xFRot - 0.01;
			//glRotatef(-0.01,0.0,1.0,1.0);
			glutPostRedisplay();
			break;

	case 'Y':	// Rotate Positive Y
			yRot = yRot + 0.5;
			yFRot = yFRot + 0.01;
			//glRotatef(0.01,1.0,0.0,1.0);
			glutPostRedisplay();
			break;

	case 'y':	// Rotate Negative Y
			yRot = yRot - 0.5;
			yFRot = yFRot - 0.01;
			//glRotatef(-0.01,1.0,0.0,1.0);
			glutPostRedisplay();
			break;
			
	case 'F': case 'f': // Fast animation
			autoDec = autoDec + 0.01;
			glutPostRedisplay();
			break;
			
	case 'S': case 's': // Slow animation
			if(autoDec > 0)
			{
			  autoDec = autoDec - 0.01;
			}
			else
			{
			  autoDec = 0.05; // if autorun decrement is lower than 0, reset to original decrement.
			}
			glutPostRedisplay();
			break;
			
	case 'A': case 'a': // Invoke some kind of pre-defined animation
			glutIdleFunc(Auto);
			glutPostRedisplay();
			break;
			
	case 'T': case 't': // Pause animation
			autoDec = 0;
			glutPostRedisplay();
			break;
	
	case 'C': case 'c': // Resume Animation
			autoDec = 0.05;
			glutPostRedisplay();
			break;
			
	case 'P': // Switch rendering to the flat shaded polygonization
			glShadeModel(GL_FLAT);
			glutPostRedisplay();
			break;
			
	case 'p': // Switch rendering to the smooth shaded polygonization
			glShadeModel(GL_SMOOTH);
			glutPostRedisplay();
			break;		

	default:
				break;
	}
}
void main(int a,char ** b) // Main for the execution of the program.
{
	glutInit(&a,b);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(500,350);  // Position of the initial window
	glutInitWindowSize(1000,700); // Size of the window
	glutCreateWindow("CG - Under The Sea");
	settings(); // Activate the initial settings for the scene
	doLights(); // Activates light sources for the scene
	glutIdleFunc(animation);
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard); // Detects any input done through the keyboard
	glutMainLoop();
}
