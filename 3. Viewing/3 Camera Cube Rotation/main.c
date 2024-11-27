#include <GL/glut.h>
#include <stdlib.h>

static float angle = 0.0; // Rotation angle around the Y-axis

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0); // Background color: black
   glShadeModel(GL_FLAT);            // Flat shading (no gradient)
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0); // Cube color: white
   
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 2.5,   // Fixed camera position
             0.0, 0.0, 0.0,   // Point the camera is looking at
             0.0, 1.0, 0.0);  // "Up" vector

   glRotatef(angle, 0.0, 1.0, 0.0); // Rotation around the Y-axis
   glutWireCube(1.0);               // Draw the cube

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // Perspective projection
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: // ESC
         exit(0);
         break;
   }
}

void timer(int value)
{
   angle += 1.3; // Increment rotation angle
   if (angle >= 360.0) angle -= 360.0; // Keep angle within [0, 360)
   glutPostRedisplay(); // Request window redraw
   glutTimerFunc(16, timer, 0); // Call itself after 16 ms (~60 FPS)
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow("OpenGL 16*Code - Camera Cube Rotation - 18/11/2024 22:51");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(16, timer, 0); // Start the timer
   glutMainLoop();
   return 0;
}
