#include <GL/freeglut.h>

// Macro to calculate buffer offset
#define BUFFER_OFFSET(offset)  ((GLvoid*) NULL + offset)
// Macro to calculate the number of elements in an array
#define NumberOf(array)        (sizeof(array)/sizeof(array[0]))

// Structure to hold 3D vector data (x, y, z)
typedef struct {
    GLfloat x, y, z;
} vec3;

// Structure to hold transformation data (translation, rotation angle, and axis)
typedef struct {
    vec3     xlate;   // Translation vector
    GLfloat  angle;   // Rotation angle
    vec3     axis;    // Rotation axis
} XForm;

// Enum for different objects (Cube, Cone)
enum { Cube, Cone, NumVAOs };

// VAO array to store the vertex array objects
GLuint   VAO[NumVAOs];
// Primitive type for each object (cube, cone)
GLenum   PrimType[NumVAOs];
// Number of elements (indices) for each object
GLsizei  NumElements[NumVAOs];
// Transformation data for each object
XForm    Xform[NumVAOs] = {
    { { -2.0, 0.0, 0.0 }, 0.0, { 0.0, 1.0, 0.0 } }, // Cube
    { {  0.0, 0.0, 2.0 }, 0.0, { 1.0, 0.0, 0.0 } }  // Cone
};
// Angle for rotating the scene
GLfloat  Angle = 0.0;

// Initialization function to set up objects and their transformations
void init()
{
    // Enum to represent different buffer types (vertices, colors, elements)
    enum { Vertices, Colors, Elements, NumVBOs };
    GLuint  buffers[NumVBOs];  // Buffer array for storing vertex data

    // Generate Vertex Array Objects (VAOs) for the cube and cone
    glGenVertexArrays(NumVAOs, VAO);

    // Set up the cube object
    {
        GLfloat  cubeVerts[][3] = {
            { -1.0, -1.0, -1.0 },
            { -1.0, -1.0,  1.0 },
            { -1.0,  1.0, -1.0 },
            { -1.0,  1.0,  1.0 },
            {  1.0, -1.0, -1.0 },
            {  1.0, -1.0,  1.0 },
            {  1.0,  1.0, -1.0 },
            {  1.0,  1.0,  1.0 },
        };

        GLfloat  cubeColors[][3] = {
            {  0.0,  0.0,  0.0 },
            {  0.0,  0.0,  1.0 },
            {  0.0,  1.0,  0.0 },
            {  0.0,  1.0,  1.0 },
            {  1.0,  0.0,  0.0 },
            {  1.0,  0.0,  1.0 },
            {  1.0,  1.0,  0.0 },
            {  1.0,  1.0,  1.0 },
        };

        GLubyte  cubeIndices[] = {
            0, 1, 3, 2,
            4, 6, 7, 5,
            2, 3, 7, 6,
            0, 4, 5, 1,
            0, 2, 6, 4,
            1, 5, 7, 3
        };

        // Bind the cube VAO and generate buffers
        glBindVertexArray(VAO[Cube]);
        glGenBuffers(NumVBOs, buffers);
        
        // Set up the vertex buffer for cube
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts),
             cubeVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        // Set up the color buffer for cube
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors),
            cubeColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        // Set up the index buffer for cube
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
            buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        // Define primitive type and number of elements for the cube
        PrimType[Cube] = GL_QUADS;
        NumElements[Cube] = NumberOf(cubeIndices);
    }

    // Set up the cone object
    {
        int i, idx;
        float  dTheta;
#define NumConePoints  36
        GLfloat  coneVerts[NumConePoints+1][3] = {
            {0.0, 0.0, 1.0}  // Apex of the cone
        };
        GLfloat  coneColors[NumConePoints+1][3] = {
            {1.0, 1.0, 1.0}  // Color for the apex
        };
        GLubyte  coneIndices[NumConePoints+1];

        // Calculate angle step for the cone
        dTheta = 2 * M_PI / (NumConePoints - 1);
        idx = 1;
        for (i = 0; i < NumConePoints; ++i, ++idx) {
            float theta = i * dTheta;
            coneVerts[idx][0] = cos(theta);  // X coordinate
            coneVerts[idx][1] = sin(theta);  // Y coordinate
            coneVerts[idx][2] = 0.0;         // Z coordinate at base

            // Set colors for cone vertices
            coneColors[idx][0] = cos(theta);
            coneColors[idx][1] = sin(theta);
            coneColors[idx][2] = 0.0;

            coneIndices[idx] = idx;  // Index for the base vertices
        }

        // Bind the cone VAO and generate buffers
        glBindVertexArray(VAO[Cone]);
        glGenBuffers(NumVBOs, buffers);
        
        // Set up the vertex buffer for cone
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts),
            coneVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        // Set up the color buffer for cone
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors),
            coneColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        // Set up the index buffer for cone
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
            buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);

        // Define primitive type and number of elements for the cone
        PrimType[Cone] = GL_TRIANGLE_FAN;
        NumElements[Cone] = NumberOf(coneIndices);
    }

    // Enable depth testing for correct rendering of 3D objects
    glEnable(GL_DEPTH_TEST);
}

// Display function to render the objects (cube and cone)
void display()
{
    int  i;

    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the current transformation matrix
    glPushMatrix();
    glRotatef(Angle, 0.0, 1.0, 0.0);  // Rotate the scene around the Y-axis

    // Render each object (cube and cone) with their transformations
    for (i = 0; i < NumVAOs; ++i) {
        glPushMatrix();  // Save the current transformation matrix
        glTranslatef(Xform[i].xlate.x, Xform[i].xlate.y,
            Xform[i].xlate.z);  // Apply translation
        glRotatef(Xform[i].angle, Xform[i].axis.x,
            Xform[i].axis.y, Xform[i].axis.z);  // Apply rotation
        glBindVertexArray(VAO[i]);  // Bind the corresponding VAO
        glDrawElements(PrimType[i], NumElements[i],
            GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));  // Draw the object
        glPopMatrix();  // Restore the previous transformation matrix
    }

    glPopMatrix();  // Restore the previous transformation matrix
    glutSwapBuffers();  // Swap the front and back buffers for double buffering
}
