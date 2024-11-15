#include <GL/glut.h>  // Necessary library for OpenGL and GLUT

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] = {
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};

static GLuint tindices[20][3] = {
  {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
  {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
  {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
  {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
};

int i;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
    glLoadIdentity(); // Reset the transformation matrix

    // Set the camera position and orientation
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < 20; i++) {
        // Define colors for each vertex (just for example)
        glColor3f(1.0f, 1.0f, 1.0f); // Vertex 1 - Red
        glVertex3fv(&vdata[tindices[i][0]][0]);

        glColor3f(0.0f, 0.0f, 0.0f); // Vertex 2 - whiote
        glVertex3fv(&vdata[tindices[i][1]][0]);

        glColor3f(0.0f, 0.0f, 1.0f); // Vertex 3 - Blue
        glVertex3fv(&vdata[tindices[i][2]][0]);
    }
    glEnd();

    glutSwapBuffers(); // Swap the buffers (double buffering)
}

void init(void) {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper 3D rendering
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the background color to black

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION); // Set the projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Define a perspective field of view
    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use double buffering and depth buffer
    glutInitWindowSize(600, 400); // Window size
    glutCreateWindow("OpenGL 12*Code - GL Client State - 14/11/2024 23:42");
    
    init();
    glutDisplayFunc(display); // Function to draw the object
    glutMainLoop(); // Start the main rendering loop

    return 0;
}
