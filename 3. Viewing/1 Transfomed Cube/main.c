#include<GL/freeglut.h>
#include <stdlib.h>

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Background color: black
    glShadeModel(GL_FLAT);             // Flat shading (no gradient)
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Cube color: white
    glLoadIdentity(); /* Clear the matrix */
        /* Viewing transformation */
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Camera position and orientation
        glScalef(1.0, 2.0, 1.0); // Scaling transformation
        glutWireCube(1.0); // Draw the cube
        glFlush();
}

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    
    glutInitWindowPosition(100, 010);
    glutCreateWindow("OpenGL 14*Code - Transformed Cube - 15/11/2024 22:01");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
