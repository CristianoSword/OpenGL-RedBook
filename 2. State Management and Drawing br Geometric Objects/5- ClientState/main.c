#include <GL/glut.h>

// Define the coordinates of the vertices for a square
GLfloat vertices[] = {
    -0.5, -0.5, 0.0,  // Vertex 1 (bottom-left)
     0.5, -0.5, 0.0,  // Vertex 2 (bottom-right)
     0.5,  0.5, 0.0,  // Vertex 3 (top-right)
    -0.5,  0.5, 0.0   // Vertex 4 (top-left)
};

// Define the colors for each vertex
GLfloat colors[] = {
    1.0, 0.0, 0.0,  // Color of vertex 1 (red)
    0.0, 1.0, 0.0,  // Color of vertex 2 (green)
    0.0, 0.0, 1.0,  // Color of vertex 3 (blue)
    1.0, 1.0, 0.0   // Color of vertex 4 (yellow)
};

// Display function that is called to render the scene
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer (screen)

    // Enable client-side arrays for vertices and colors
    glEnableClientState(GL_VERTEX_ARRAY);   // Enable the vertex array
    glEnableClientState(GL_COLOR_ARRAY);    // Enable the color array

    // Set the pointer to the vertex array
    glVertexPointer(3, GL_FLOAT, 0, vertices);  // 3 components per vertex (x, y, z)
    
    // Set the pointer to the color array
    glColorPointer(3, GL_FLOAT, 0, colors);    // 3 components per color (red, green, blue)

    // Draw the square using the vertices and colors
    glDrawArrays(GL_QUADS, 0, 4);  // Draw a quadrilateral (square) with 4 vertices

    // Disable the client-side arrays after drawing
    glDisableClientState(GL_VERTEX_ARRAY);  // Disable the vertex array
    glDisableClientState(GL_COLOR_ARRAY);   // Disable the color array

    glFlush();  // Flush the OpenGL pipeline to ensure the drawing is done
}

// Initialization function to set up OpenGL parameters
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
}

// Main function to set up the window and OpenGL context
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode to single buffer and RGB color
    glutInitWindowSize(400, 400);  // Set window size to 400x400 pixels
    glutCreateWindow("OpenGL 11*Code - GL Client State - 12/11/2024 23:26");  // Create window with title
    init();  // Call the initialization function
    glutDisplayFunc(display);  // Register the display function to render the scene
    glutMainLoop();  // Start the GLUT main loop, making the application interactive
    return 0;  // Return 0 to indicate successful execution
}
