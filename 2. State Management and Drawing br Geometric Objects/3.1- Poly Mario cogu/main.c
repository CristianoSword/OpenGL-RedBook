#include <GL/glut.h>

// Function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the red hat of the mushroom
    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.0);   // Left bottom corner
        glVertex2f(-0.3, 0.3);   // Top left corner
        glVertex2f(0.3, 0.3);    // Top right corner
        glVertex2f(0.5, 0.0);    // Right bottom corner
        glVertex2f(0.3, -0.3);   // Right inner bottom corner
        glVertex2f(-0.3, -0.3);  // Left inner bottom corner
    glEnd();

    // Draw the white face of the mushroom
    glColor3f(1.0, 1.0, 1.0);  // Set color to white
    glBegin(GL_POLYGON);
        glVertex2f(-0.3, -0.3);  // Left bottom corner
        glVertex2f(0.3, -0.3);   // Right bottom corner
        glVertex2f(0.3, -0.6);   // Right lower corner
        glVertex2f(-0.3, -0.6);  // Left lower corner
    glEnd();

    // Draw the black eyes
    glColor3f(0.0, 0.0, 0.0);  // Set color to black
    glBegin(GL_POLYGON); // Left eye
        glVertex2f(-0.15, -0.4);
        glVertex2f(-0.1, -0.4);
        glVertex2f(-0.1, -0.5);
        glVertex2f(-0.15, -0.5);
    glEnd();

    glBegin(GL_POLYGON); // Right eye
        glVertex2f(0.1, -0.4);
        glVertex2f(0.15, -0.4);
        glVertex2f(0.15, -0.5);
        glVertex2f(0.1, -0.5);
    glEnd();

    glFlush();  // Ensure all rendering is completed
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background color to black
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Set up orthographic projection
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowSize(450, 450);  // Set window size
    glutCreateWindow("OpenGL 9*Code - Mushroom - 12/11/2024 22:16");  // Create window with title
    init();  // Initialize OpenGL settings
    glutDisplayFunc(display);  // Register display function
    glutMainLoop();  // Enter GLUT main loop
    return 0;
}
