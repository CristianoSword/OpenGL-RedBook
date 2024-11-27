#include <GL/freeglut.h> // Include the FreeGLUT library for creating OpenGL windows and handling events

// Function to display the triangle
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer to prepare for new drawing
    glBegin(GL_TRIANGLES); // Start drawing a triangle using OpenGL's GL_TRIANGLES primitive
        glVertex3f(-0.5, -0.5, 0.0); // Specify the first vertex of the triangle (bottom left)
        glVertex3f( 0.5, -0.5, 0.0); // Specify the second vertex of the triangle (bottom right)
        glVertex3f( 0.0,  0.5, 0.0); // Specify the third vertex of the triangle (top center)
    glEnd(); // End drawing the triangle
    glFlush(); // Ensure all OpenGL commands are executed and rendered
}

// Main function to initialize the window and start the event loop
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT (handles command line arguments and initialization)
    glutCreateWindow("OpenGL 3*code - 20/09/2024 22:56"); // Create a window with the specified title
    glutDisplayFunc(display); // Register the display function that will be called to render the scene
    glutMainLoop(); // Start the GLUT event loop to handle window events and display updates
    return 0; // Return 0 to indicate successful execution (though this is never reached)
}
