#include <GL/freeglut.h>

// system solar sphere 3D

static GLfloat spin = 0.0;
static GLfloat spinOrbit = 0.0;
static GLfloat speed = 50.0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	// sun
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutWireSphere(1.5, 20, 20);
	glPopMatrix();

	// earth
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(spinOrbit, 0.0, 0.0, 1.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutWireSphere(0.2, 20, 20);
	glPopMatrix();

	// mars
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(spinOrbit, 0.0, 0.0, 1.0);
	glTranslatef(4.0, 2.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glutWireSphere(0.4, 20, 20);
	glPopMatrix();

	glutSwapBuffers();

}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble) w / (GLdouble) h, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	if (spin > 360.0)
		spin = 0.0;
	if (spinOrbit > 360.0)
		spinOrbit = 0.0;
	spin = spin + 0.01 * speed;
	spinOrbit = spinOrbit + 0.01 * speed;
	display();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 010);
	glutCreateWindow("Simple Solar System");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}