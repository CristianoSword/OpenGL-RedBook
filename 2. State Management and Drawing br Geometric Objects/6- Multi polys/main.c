#include <GL/freeglut.h>

// Define vertex positions (triangle vertices)
float vertices[] = {
    0.0f,  0.5f, 0.0f,  // Vertex 0 (top)
    -0.5f, -0.5f, 0.0f, // Vertex 1 (bottom-left)
    0.5f, -0.5f, 0.0f,  // Vertex 2 (bottom-right)
};

// Define vertex colors (RGB for each vertex)
float colors[] = {
    1.0f, 0.0f, 0.0f, // Red for Vertex 0
    0.0f, 1.0f, 0.0f, // Green for Vertex 1
    0.0f, 0.0f, 1.0f, // Blue for Vertex 2
};

// Define texture coordinates for each vertex
float texCoords[] = {
    0.0f, 1.0f, // Texture coordinate for Vertex 0
    1.0f, 1.0f, // Texture coordinate for Vertex 1
    0.5f, 0.0f, // Texture coordinate for Vertex 2
};

// Declare VBOs (for vertices, colors, and texture coordinates) and VAO (for vertex array object)
GLuint vbo[3];  // VBOs for vertices, colors, and texture coordinates
GLuint vao;     // VAO to group the VBOs

int stride = sizeof(float) * 3; // Size of the stride for vertex attributes

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer (screen)

    // Enable the vertex, color, and texture coordinate arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Set the pointer for vertex array
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);  // Point to vertex data (3 components per vertex)

    // Set the pointer for color array
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glColorPointer(3, GL_FLOAT, 0, (void*)0);  // Point to color data (3 components per color)

    // Set the pointer for texture coordinate array
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);  // Point to texture coordinate data (2 components per texture coordinate)

    // Draw the triangle using the vertex, color, and texture data
    glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw a triangle with 3 vertices

    // Disable the arrays after rendering
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();  // Swap buffers (for double buffering)
}

// Initialization function to set up OpenGL parameters
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black

    // Generate and bind the VBOs
    glGenBuffers(3, vbo);  // Generate 3 VBOs

    // VBO for vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // VBO for colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // VBO for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    // Generate and bind the VAO
    glGenVertexArrays(1, &vao);  // Generate 1 VAO
    glBindVertexArray(vao);      // Bind the VAO
}

// Reshape function to adjust the viewport and projection
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Set the viewport to the window size
    glMatrixMode(GL_PROJECTION);  // Switch to projection matrix
    glLoadIdentity();              // Load identity matrix
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set orthographic projection
    glMatrixMode(GL_MODELVIEW);         // Switch back to modelview matrix
}

// Main function to initialize GLUT and set up the window
int main(int argc, char** argv) {
    glutInit(&argc, argv);                     // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set display mode (double buffering and RGB)
    glutInitWindowSize(500, 500);               // Set window size
    glutCreateWindow("OpenGL Freeglut Example");  // Create window with title

    init();  // Call the initialization function

    glutDisplayFunc(display);   // Set the display function to render the scene
    glutReshapeFunc(reshape);   // Set the reshape function for window resizing

    glutMainLoop();  // Start the GLUT main loop (keeps the program running)
    return 0;        // Return 0 to indicate successful execution
}
