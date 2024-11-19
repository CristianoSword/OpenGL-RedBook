#include <GL/glut.h>  // Include the GLUT and OpenGL libraries
#include <math.h>

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

void normalize(GLfloat *v)
{
    GLfloat len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (len > 0.0) {
        v[0] /= len;
        v[1] /= len;
        v[2] /= len;
    }
}

void drawtriangle(float *v1, float *v2, float *v3)
{
   glBegin(GL_TRIANGLES);

  

      // Apply normal and color for each vertex
      glNormal3fv(v1);
      glColor3f(1.0f, 1.0f, 1.0f); // White color for Vertex 1
      glVertex3fv(v1);

      glNormal3fv(v2);
      glColor3f(1.0f, 1.0f, 1.0f); // Black color for Vertex 2
      glVertex3fv(v2);

      glNormal3fv(v3);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue color for Vertex 3
      glVertex3fv(v3);

   

   glEnd();
}

void subdivide(float *v1, float *v2, float *v3)
{
   GLfloat v12[3], v23[3], v31[3];
   GLint i;

   for (i = 0; i < 3; i++) {
      v12[i] = (v1[i] + v2[i]) / 2.0;
      v23[i] = (v2[i] + v3[i]) / 2.0;
      v31[i] = (v3[i] + v1[i]) / 2.0;
   }
   normalize(v12);
   normalize(v23);
   normalize(v31);

   drawtriangle(v1, v12, v31);
   drawtriangle(v2, v23, v12);
   drawtriangle(v3, v31, v23);
   drawtriangle(v12, v23, v31);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
    glLoadIdentity(); // Reset the transformation matrix

    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set camera position and orientation

    // Loop through each triangle index and subdivide it
    for (int i = 0; i < 20; i++) {
        subdivide(&vdata[tindices[i][0]][0],
                  &vdata[tindices[i][1]][0],
                  &vdata[tindices[i][2]][0]);
    }

    glutSwapBuffers(); // Swap buffers for double buffering
}

void init(void) {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set the background color to black

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION); // Set the projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Set the perspective field of view
    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use double buffering and depth buffer
    glutInitWindowSize(800, 600); // Set the window size
    glutCreateWindow("OpenGL 12*Code - Single Subdivided Icosahedron - 15/11/2024 00:01");
 
    init();
    glutDisplayFunc(display); // Set the display function
    glutMainLoop(); // Start the main rendering loop

    return 0;
}
