#include <GL/glut.h>

// Initial camera position
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;

void display() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the transformation matrix
    glLoadIdentity();

    // Set up the camera using gluLookAt
    gluLookAt(cameraX, cameraY, cameraZ,   // Camera position
              0.0, 0.0, 0.0,              // Look-at point
              0.0, 1.0, 0.0);             // Up vector

    // Draw a cube at the center
    glColor3f(1.0, 0.0, 0.0);             // Set color to red
    glutWireCube(2.0);

    // Swap buffers to display the rendered frame
    glutSwapBuffers();
}

void reshape(int w, int h) {
    // Set the viewport to match the window size
    glViewport(0, 0, w, h);

    // Switch to the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define a perspective projection
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

    // Switch back to the model/view matrix
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    // Control camera position using WASD keys
    if (key == 'w') cameraZ -= 0.5f; // Move forward
    if (key == 's') cameraZ += 0.5f; // Move backward
    if (key == 'a') cameraX -= 0.5f; // Move left
    if (key == 'd') cameraX += 0.5f; // Move right

    glutPostRedisplay(); // Re-render the scene
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 15*Code - Camera Cube - 18/11/2024 22:41");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set up callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Enter the GLUT main loop
    glutMainLoop();
    return 0;
}
