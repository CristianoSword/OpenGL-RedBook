#include <GL/glut.h>  // GLUT library for windows and events

// Function to draw a convex polygon (square)
void desenhaPoligonoConvexo(void) {
    // Draw a square
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.8f);  // Bottom-left vertex
        glVertex2f(-0.2f, -0.8f);  // Bottom-right vertex
        glVertex2f(-0.2f, -0.2f);  // Top-right vertex
        glVertex2f(-0.8f, -0.2f);  // Top-left vertex
    glEnd();
}

// Function to draw a non-convex polygon (concave)
void desenhaPoligonoNaoConvexo(void) {
    // Draw a concave shape (star)
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.8f);   // Top vertex
        glVertex2f(0.2f, 0.2f);   // Bottom-right vertex
        glVertex2f(0.8f, 0.2f);   // External right point
        glVertex2f(0.3f, -0.2f);  // Inner bottom-right vertex
        glVertex2f(0.5f, -0.8f);  // External bottom point
        glVertex2f(0.0f, -0.4f);  // Inner central bottom point
        glVertex2f(-0.5f, -0.8f); // External bottom-left point
        glVertex2f(-0.3f, -0.2f); // Inner bottom-left vertex
        glVertex2f(-0.8f, 0.2f);  // External left point
        glVertex2f(-0.2f, 0.2f);  // Bottom-left vertex
    glEnd();
}

// Rendering function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Clears the screen

    // Draw the convex polygon on the left
    // desenhaPoligonoConvexo();

    // Draw the non-convex polygon on the right
    desenhaPoligonoNaoConvexo();

    glFlush();  // Ensures that the drawing commands are executed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initializes GLUT
    glutCreateWindow("OpenGL 6*Code - Poly no Convex- 27/09/2024 22:59");  // Creates a window
    glutDisplayFunc(display);  // Rendering function
    glutMainLoop();  // Event loop
    return 0;
}
