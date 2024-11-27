#include <GL/freeglut.h>

// Solar system sphere 3D simulation

// Global variables for rotation and orbit speed
static GLfloat spin = 0.0;
static GLfloat spinOrbit = 0.0;
static GLfloat speed = 50.0;  // Speed of rotation and orbit

// Initialization function to set up OpenGL state
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glShadeModel(GL_FLAT); // Set shading model to flat (no smooth shading)
}

// Display function to render the scene
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glMatrixMode(GL_MODELVIEW); // Set the current matrix mode to modelview

    glLoadIdentity(); // Reset the current matrix
    gluLookAt(0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0); // Set the camera position

    // Draw the sun
    glPushMatrix(); // Save the current transformation matrix
    glColor3f(1.0, 0.0, 0.0); // Set color to red for the sun
    glTranslatef(0.0, 0.0, 0.0); // Move to the sun's position (origin)
    glRotatef(spin, 0.0, 0.0, 1.0); // Rotate the sun
    glutWireSphere(1.5, 20, 20); // Draw a wireframe sphere (sun)
    glPopMatrix(); // Restore the previous transformation matrix

    // Draw the Earth
    glPushMatrix(); // Save the current transformation matrix
    glColor3f(0.5, 0.5, 0.5); // Set color to gray for Earth
    glRotatef(spinOrbit, 0.0, 0.0, 1.0); // Rotate the Earth around the sun
    glTranslatef(2.0, 0.0, 0.0); // Translate Earth 2 units along the x-axis (orbit radius)
    glRotatef(spin, 0.0, 0.0, 1.0); // Rotate the Earth on its axis
    glutWireSphere(0.2, 20, 20); // Draw a wireframe sphere (Earth)
    glPopMatrix(); // Restore the previous transformation matrix

    // Draw Mars
    glPushMatrix(); // Save the current transformation matrix
    glColor3f(0.5, 0.5, 0.5); // Set color to gray for Mars
    glRotatef(spinOrbit, 0.0, 0.0, 1.0); // Rotate Mars around the sun
    glTranslatef(4.0, 2.0, 0.0); // Translate Mars 4 units along the x-axis and 2 units along the y-axis
    glRotatef(spin, 0.0, 0.0, 1.0); // Rotate Mars on its axis
    glutWireSphere(0.4, 20, 20); // Draw a wireframe sphere (Mars)
    glPopMatrix(); // Restore the previous transformation matrix

    glutSwapBuffers(); // Swap the front and back buffers for double buffering
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // Set the viewport size
    glMatrixMode(GL_PROJECTION); // Set the current matrix mode to projection
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(40.0, (GLdouble) w / (GLdouble) h, 0.5, 20.0); // Set the perspective projection
    glMatrixMode(GL_MODELVIEW); // Set the current matrix mode back to modelview
}

// Idle function for animation (called continuously during idle time)
void idle(void) {
    // Reset the rotation angles if they exceed 360 degrees
    if (spin > 360.0)
        spin = 0.0;
    if (spinOrbit > 360.0)
        spinOrbit = 0.0;

    // Increment the rotation and orbit angles
    spin = spin + 0.01 * speed; // Rotate the sun and planets on their axes
    spinOrbit = spinOrbit + 0.01 * speed; // Rotate the planets around the sun
    display(); // Redraw the scene
}

// Main function to initialize OpenGL, create window, and start the event loop
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode to double buffer and RGB color model
    glutInitWindowSize(1000, 700); // Set the window size to 1000x700 pixels
    
    glutInitWindowPosition(100, 10); // Set the window position on the screen
    glutCreateWindow("OpenGL Solar System Simulation"); // Create the window with a title
    init(); // Initialize OpenGL state
    glutDisplayFunc(display); // Set the display callback function
    glutReshapeFunc(reshape); // Set the reshape callback function
    glutIdleFunc(idle); // Set the idle callback function for animation
    glutMainLoop(); // Enter the GLUT main loop (event processing)
    return 0;
}
