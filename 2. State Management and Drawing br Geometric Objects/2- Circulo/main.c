#include <GL/glut.h>
#include <math.h>  // For trigonometric functions

// Function to draw a circle using line approximation
void desenhaCirculo(float raio, int numSegmentos) {
    glBegin(GL_LINE_LOOP);  // Start the closed line loop (circle approximation)
    for (int i = 0; i < numSegmentos; i++) {
        float angulo = 2.0f * 3.14 * i / numSegmentos;  // Angle in radians
        float x = raio * cos(angulo);  // X coordinate
        float y = raio * sin(angulo);  // Y coordinate
        glVertex2f(x, y);  // Define the vertex at the calculated position
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Clears the screen

    // Draw a circle with 100 segments (reasonable approximation)
    desenhaCirculo(0.5f, 100);

    glFlush();  // Ensures that drawing commands are executed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL 7*Code - Circle Line Curves - 27/09/2024 23:09");
    glutDisplayFunc(display);  // Rendering function
    glutMainLoop();  // Event loop
    return 0;
}
