#include <GL/freeglut.h> // Include the FreeGLUT library for window management and OpenGL functionality

// Double Buffered Rotating Square program
// ERROR: No display callback registered for window 1

static GLfloat spin = 0.0; // Angle for rotating the square

// Initialize OpenGL settings
void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glShadeModel(GL_FLAT); // Set shading model to flat shading
}

// Function to display the rotating square
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glPushMatrix(); // Save the current matrix state (for later restoration)
    glRotatef(spin, 0.0, 0.0, 1.0); // Rotate the square by 'spin' degrees around the Z-axis
    glColor3f(1.0, 1.0, 1.0); // Set square color to white
    glRectf(-25.0, -25.0, 25.0, 25.0); // Draw a square centered at (0, 0) with width and height of 50 units
    glPopMatrix(); // Restore the previous matrix state
    
    glutSwapBuffers(); // Swap the front and back buffers for double buffering (smooth animation)
}

// Function to increment the rotation angle for continuous rotation
void spinDisplay(void){
    spin = spin + 2.0; // Increment the spin angle
    if (spin > 360.0) // If the angle exceeds 360 degrees, reset it to keep the range within 0-360 degrees
        spin = spin - 360.0;
    glutPostRedisplay(); // Request a redraw of the window
}

// Function to handle window resizing and adjust the viewport
void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // Set the viewport to the new window size
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity(); // Load the identity matrix to reset the projection
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0); // Set up an orthographic projection with a 100x100 view area centered at (0, 0)
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix mode
    glLoadIdentity(); // Reset the modelview matrix to the identity matrix
}

// Function to handle mouse input (start and stop the rotation)
void mouse(int button, int state, int x, int y){
    switch (button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) // When the left mouse button is pressed
                glutIdleFunc(spinDisplay); // Start rotating the square (by calling spinDisplay)
            break;
        case GLUT_MIDDLE_BUTTON:
            if(state == GLUT_DOWN) // When the middle mouse button is pressed
                glutIdleFunc(NULL); // Stop the rotation (no function is called in idle mode)
            break;
        default:
            break;
    }
}

/*
*  Request double buffer display mode.
*  Register mouse input callback functions
*/

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT (handles command line arguments and OpenGL initialization)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode to double buffering and RGB color mode
    glutInitWindowSize(400, 400); // Set the window size to 400x400 pixels
    glutInitWindowPosition(100, 100); // Set the window position on the screen
    glutCreateWindow("OpenGL 4*Code - 21/09/2024 11:41"); // Create the window with the given title
    
    init(); // Initialize OpenGL settings

    // Register the display callback function to be called during window redraw
    glutDisplayFunc(display);

    // Register other callback functions
    glutReshapeFunc(reshape); // Register the reshape function to handle window resizing
    glutMouseFunc(mouse); // Register the mouse function to handle mouse input
    
    glutMainLoop(); // Start the GLUT main loop to handle window events and render continuously
    return 0; // Return 0 (this is not reached as the main loop is continuous)
}
