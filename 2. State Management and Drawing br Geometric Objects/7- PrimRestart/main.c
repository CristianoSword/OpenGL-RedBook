#include <GL/freeglut.h>

// Macro to get the buffer offset
#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)

// Define the start and end coordinates for X and Y
#define XStart      -0.8
#define XEnd         0.8
#define YStart      -0.8
#define YEnd         0.8

// Number of points along X and Y axes
#define NumXPoints          11
#define NumYPoints          11
#define NumPoints           (NumXPoints * NumYPoints)  // Total number of points
#define NumPointsPerStrip   (2*NumXPoints)  // Points per strip (2 per row)
#define NumStrips           (NumYPoints-1)  // Number of strips (rows - 1)
#define RestartIndex        0xFFFF  // Index used for primitive restart

// Initialization function
void init() {
    GLuint vbo, ebo;  // Vertex Buffer Object (VBO) and Element Buffer Object (EBO)
    GLfloat *vertices;  // Pointer for vertex data
    GLushort *indices;  // Pointer for index data

    /* Set up vertex data */
    // Generate and bind VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Allocate space for the vertex buffer (2 * NumPoints because each point has an x and y value)
    glBufferData(GL_ARRAY_BUFFER, 2 * NumPoints * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

    // Map the buffer for writing vertex data
    vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (vertices == NULL) {
        fprintf(stderr, "Unable to map vertex buffer\n");
        exit(EXIT_FAILURE);
    } else {
        int i, j;
        GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);  // Step size for X
        GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);  // Step size for Y
        GLfloat *tmp = vertices;  // Temporary pointer to write vertex data
        int n = 0;

        // Loop through the Y-axis points
        for (j = 0; j < NumYPoints; ++j) {
            GLfloat y = YStart + j * dy;  // Calculate the Y position

            // Loop through the X-axis points
            for (i = 0; i < NumXPoints; ++i) {
                GLfloat x = XStart + i * dx;  // Calculate the X position
                *tmp++ = x;  // Store X coordinate
                *tmp++ = y;  // Store Y coordinate
            }
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);  // Unmap the buffer
        glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));  // Set the vertex pointer
        glEnableClientState(GL_VERTEX_ARRAY);  // Enable vertex array client state
    }

    /* Set up index data */
    // Generate and bind EBO
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Allocate space for the index buffer (with an extra space for the restart index)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort), NULL, GL_STATIC_DRAW);
    indices = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

    if (indices == NULL) {
        fprintf(stderr, "Unable to map index buffer\n");
        exit(EXIT_FAILURE);
    } else {
        int i, j;
        GLushort *index = indices;  // Temporary pointer for index data
        for (j = 0; j < NumStrips; ++j) {
            GLushort bottomRow = j * NumYPoints;  // Bottom row index
            GLushort topRow = bottomRow + NumYPoints;  // Top row index

            // Loop through the points in the current strip
            for (i = 0; i < NumXPoints; ++i) {
                *index++ = topRow + i;  // Add top row vertex index
                *index++ = bottomRow + i;  // Add bottom row vertex index
            }
            *index++ = RestartIndex;  // Add the restart index to indicate the end of the strip
        }

        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);  // Unmap the index buffer
    }

    // Enable primitive restart with the specified index
    glPrimitiveRestartIndex(RestartIndex);
    glEnable(GL_PRIMITIVE_RESTART);  // Enable primitive restart feature
}

// Display function to render the scene
void display() {
    int i, start;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color and depth buffers

    glColor3f(1, 1, 1);  // Set drawing color to white
    glDrawElements(GL_TRIANGLE_STRIP,  // Use triangle strips to draw the grid
        NumStrips * (NumPointsPerStrip + 1),  // Total number of indices to draw
        GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));  // Use unsigned short for index data

    glutSwapBuffers();  // Swap the front and back buffers (for double buffering)
}
