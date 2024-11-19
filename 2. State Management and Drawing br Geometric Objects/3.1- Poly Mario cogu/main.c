#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o chapéu vermelho do cogumelo
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.0);
        glVertex2f(-0.3, 0.3);
        glVertex2f(0.3, 0.3);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.3, -0.3);
        glVertex2f(-0.3, -0.3);
    glEnd();

    // Desenha o rosto branco do cogumelo
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3, -0.3);
        glVertex2f(0.3, -0.3);
        glVertex2f(0.3, -0.6);
        glVertex2f(-0.3, -0.6);
    glEnd();

    // Desenha os olhos pretos
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15, -0.4);
        glVertex2f(-0.1, -0.4);
        glVertex2f(-0.1, -0.5);
        glVertex2f(-0.15, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.1, -0.4);
        glVertex2f(0.15, -0.4);
        glVertex2f(0.15, -0.5);
        glVertex2f(0.1, -0.5);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Fundo preto
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Configura o sistema de coordenadas
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450, 450);
    glutCreateWindow("OpenGL 9*Code - Mushroom - 12/11/2024 22:16");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
    
}
