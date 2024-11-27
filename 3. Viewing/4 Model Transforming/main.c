#include <GL/glut.h>  // Include the FreeGLUT library for OpenGL functionality

// Function to draw a triangle
void draw_triangle() {
    glBegin(GL_TRIANGLES);  // Begin drawing a triangle
    glVertex2f(0.0, 1.0);   // Top vertex
    glVertex2f(-1.0, -1.0); // Bottom-left vertex
    glVertex2f(1.0, -1.0);  // Bottom-right vertex
    glEnd();  // End drawing the triangle
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glShadeModel(GL_FLAT);  // Set shading model to flat
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    // Draw solid triangle in the default position
    glLoadIdentity();  // Reset the transformation matrix
    glColor3f(1.0, 1.0, 1.0);  // Set color to white
    draw_triangle();  // Draw the triangle

    // Draw dashed triangle (first example)
    glEnable(GL_LINE_STIPPLE);  // Enable line stippling (dashed lines)
    glLineStipple(1, 0xF0F0);  // Set dash pattern (FOFO)
    glLoadIdentity();  // Reset the transformation matrix
    glTranslatef(-3.0, 0.0, 0.0);  // Move the triangle to the left
    draw_triangle();  // Draw the dashed triangle

    glLineStipple(1, 0xF00F);  // Change dash pattern (FOOF)

    // Draw scaled triangle
    glLoadIdentity();  // Reset the transformation matrix
    glScalef(5.5, 0.5, 1.0);  // Scale the triangle (stretch in X and compress in Y)
    draw_triangle();  // Draw the scaled triangle

    // Draw rotated triangle
    glLineStipple(1, 0x8888);  // Set a new dash pattern
    glLoadIdentity();  // Reset the transformation matrix
    glRotatef(90.0, 0.0, 0.0, 1.0);  // Rotate the triangle 90 degrees around the Z-axis
    draw_triangle();  // Draw the rotated triangle

    // Disable line stippling
    glDisable(GL_LINE_STIPPLE);

    glutSwapBuffers();  // Swap the front and back buffers for double buffering
}

// Reshape function to adjust the viewport when the window is resized
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);  // Set the viewport to the new window size
    glMatrixMode(GL_PROJECTION);  // Switch to the projection matrix mode
    glLoadIdentity();  // Reset the projection matrix
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);  // Set an orthographic projection
    glMatrixMode(GL_MODELVIEW);  // Switch back to the modelview matrix mode
}

// Main function to initialize GLUT, create the window, and enter the main loop
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set display mode (double buffering, RGB color)
    glutInitWindowSize(400, 400);  // Set the window size
    glutCreateWindow("OpenGL 17*Code - Model Transforming - 27/11/2024 00:00"); // Create the window with a title

    init();  // Call the initialization function

    glutDisplayFunc(display);  // Register the display callback function
    glutReshapeFunc(reshape);  // Register the reshape callback function for window resizing

    glutMainLoop();  // Enter the main GLUT event processing loop
    return 0;  // Return 0 (this line will never be reached since the main loop is continuous)
}
