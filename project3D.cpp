#include<GL/glut.h>
#include "imageloader.h"




GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, image->width, image->height ,0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);  
	return textureId;
}

GLuint textureBrick, textureDoor, textureGrass, textureRoof, textureWindow, textureSky;

static void init(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	Image* image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\bricks.bmp");
	textureBrick = loadTexture(image);
	image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\door.bmp");
	textureDoor = loadTexture(image);
	image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\grass.bmp");
	textureGrass = loadTexture(image);
	image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\roof.bmp");
	textureRoof = loadTexture(image);
	image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\window.bmp");
	textureWindow = loadTexture(image);
	image = loadBMP("C:\\Users\\shrou\\Desktop\\textures\\sky.bmp");
	textureSky = loadTexture(image);
	delete image;
}



float angleY = 0.0;
float angleX = 0.0;

void special(int key, int x, int y) {
	switch (key) {

	//different prespectives

	case GLUT_KEY_RIGHT:		
		angleY += 1;
		if (angleY > 360)
			angleY = 0.0;
		break;
	case GLUT_KEY_LEFT:
		angleY -= 1;
		if (angleY > 360)
			angleY = 0.0;
		break;
	case GLUT_KEY_UP:
		angleX += 1;
		if (angleX > 360)
			angleX = 0.0;
		break; 
	case GLUT_KEY_DOWN:
		angleX -= 1;
		if (angleX > 360)
			angleX = 0.0;
		break;

	//transformations

	case GLUT_KEY_HOME: glTranslatef(0.1, 0, 0);
		break;
	case GLUT_KEY_END: glTranslatef(-0.1, 0, 0);
		break;
	case GLUT_KEY_PAGE_UP: glRotatef(15, 0, 0, 1);
		break;
	case GLUT_KEY_PAGE_DOWN: angleX = 0.0; angleY = 0.0; //glRotatef(-15, 0, 0, 1);
		break;

	}
	glutPostRedisplay();
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);


	/*--------------------------------scene------------------------------------------------*/
	// sky
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureSky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -10);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 1.0, 0.1);  glVertex3f(-10, 10, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(10, 10, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(10, -10, 0);
	glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-10, -10, 0);
	glEnd();
	glPopMatrix();

	// grass
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureGrass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(angleX, 1, 0, 0); //akn akhdna variable bta3 rotx ale khlas keyboard daseto
	glRotatef(angleY, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 70.0, 1);  glVertex3f(-50, -1.5, 50);
	glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-50, -1.5, -50);
	glTexCoord3f(70.0, 0.0, -1);  glVertex3f(50, -1.5, -50);
	glTexCoord3f(70.0, 70.0, 1);  glVertex3f(50, -1.5, 50);
	glEnd();
	glPopMatrix();


	/*--------------------------------front------------------------------------------------*/

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	//wall
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 2.0, 0.1);  glVertex3f(-2, 0, 1);
	glTexCoord3f(4.0, 2.0, 0.1);  glVertex3f(2, 0, 1);
	glTexCoord3f(4.0, 0.0, 0.1);  glVertex3f(2, -1.5, 1);
	glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-2, -1.5, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//roof
	//glBegin(GL_TRIANGLES);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(4.0, 0.0, 1.25); glVertex3f(2.2, -0.1, 1.25);
	glTexCoord3f(0.0, 0.0, 1.25); glVertex3f(-2.2, -0.1, 1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureDoor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//door
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.3, -1.5, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-0.3, -1.5, 1.0001);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureWindow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//window el ala l shemal
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(-0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(-0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-1.5, -0.8, 1.0001);
	glEnd();
	//window el ala l yemen
	glBegin(GL_QUADS); 
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, 1.0001);
	glEnd();
	glPopMatrix();


	/*--------------------------------back------------------------------------------------*/

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(angleX, 1, 0, 0); //akn akhdna variable bta3 rotx ale khlas keyboard daseto
	glRotatef(angleY, 0, 1, 0);
	//wall
	glBegin(GL_QUADS); 
	glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-2, 0, -1);
	glTexCoord3f(4.0, 2.0, -1);  glVertex3f(2, 0, -1);
	glTexCoord3f(4.0, 0.0, -1);  glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-2, -1.5, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//roof
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(4.0, 0.0, -1.25); glVertex3f(2.2, -0.1, -1.25);
	glTexCoord3f(0.0, 0.0, -1.25); glVertex3f(-2.2, -0.1, -1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureWindow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  
	// window shemal
	glTexCoord3f(0.0, 1.0, -1.0001); glVertex3f(-1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, -1.0001); glVertex3f(-0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, -1.0001); glVertex3f(-0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, -1.0001); glVertex3f(-1.5, -0.8, -1.0001);
	glEnd();

	glBegin(GL_QUADS);  
	// window yemen
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, -1.0001);
	glEnd();
	glPopMatrix();

	/*--------------------------------right------------------------------------------------*/

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(angleX, 1, 0, 0); //akn akhdna variable bta3 rotx ale khlas keyboard daseto
	glRotatef(angleY, 0, 1, 0);
	//wall
	glBegin(GL_QUADS); 
	glTexCoord3f(0.0, 2.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1); glVertex3f(2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1); glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1); glVertex3f(2, -1.5, 1);
	glEnd();

	//wall traingled upper
	glBegin(GL_TRIANGLES); 
	glTexCoord3f(0.0, 1.0, 0); glVertex3f(2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1); glVertex3f(2, 0, -1);
	glEnd();
	glPopMatrix();

	/*--------------------------------left------------------------------------------------*/

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glBegin(GL_QUADS);  
	// wall
	glTexCoord3f(0.0, 2.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1);    glVertex3f(-2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1);    glVertex3f(-2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1);    glVertex3f(-2, -1.5, 1);
	glEnd();

	//wall traingled upper
	glBegin(GL_TRIANGLES); 
	glTexCoord3f(0.0, 1.0, 0);    glVertex3f(-2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1);    glVertex3f(-2, 0, -1);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}



void lights() {
	GLfloat lightPosition[] = { 0,0,5 };
	GLfloat lightColor[] = { 1,1,0 };
	GLfloat ambColor[] = { 0,0,1 }; //aghyr l var w ashof el effect

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambColor);

	//andi light sources kter f opengl , I often use first light which is gl light 0
	glEnable(GL_LIGHT0); //hdelo post w color baa
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(600, 600);
	glutCreateWindow("3D MODELING with different prespectives, movements, textures, and lightning");
	glEnable(GL_DEPTH_TEST);

	//init()
	glutReshapeFunc(init);
	glutSpecialFunc(special); 
	glutDisplayFunc(display);
	lights();

	glutMainLoop();
}
