/*
 * Draw a simple sphere using OpenGL.
 */
 
#include <GL/glut.h> // Include the FreeGLUT library for OpenGL functionality

// Function to initialize OpenGL settings
void init(void) {
    glClearColor(9.0, 9.0, 9.0, 0.0); // Set background color to light gray (RGB: 9, 9, 9)
    glShadeModel(GL_FLAT); // Set the shading model to flat shading
}

// Function to display the sphere
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glColor3f(0.0, 0.0, 0.0); // Set the sphere color to black
    glutWireSphere(2.0, 30, 36); // Draw a wireframe sphere with a radius of 2, 30 slices (longitude), and 36 stacks (latitude)
    glutSwapBuffers(); // Swap the front and back buffers for double buffering (smooth animation)
}

// Function to handle window resizing and adjust the viewport and projection
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    gluPerspective(50.0, w / (GLfloat) h, 3.0, 90.0); // Set a perspective projection with a field of view of 50 degrees, aspect ratio, near and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix mode
    gluLookAt(2.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera's position and orientation (view from 2, 4, 5, looking at the origin with the up vector pointing along the Y-axis)
}

// Main function to initialize GLUT, create a window, and start the rendering loop
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT (handles command line arguments and OpenGL initialization)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode to double buffering and RGB color mode
    glutInitWindowSize(960, 960); // Set the window size to 960x960 pixels
    glutInitWindowPosition(10, 10); // Set the window position on the screen
    glutCreateWindow("OpenGL 5*Code - 21/09/2024 17:41"); // Create the window with the given title
    
    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display callback function
    glutReshapeFunc(reshape); // Register the reshape callback function for window resizing
    
    glutMainLoop(); // Start the GLUT main loop to handle window events and render continuously
    return 0; // Return 0 (this is not reached as the main loop is continuous)
}
