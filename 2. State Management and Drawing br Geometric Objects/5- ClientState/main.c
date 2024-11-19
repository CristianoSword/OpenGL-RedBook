#include <GL/glut.h>

GLfloat vertices[] = {
    -0.5, -0.5, 0.0,  // Vértice 1
     0.5, -0.5, 0.0,  // Vértice 2
     0.5,  0.5, 0.0,  // Vértice 3
    -0.5,  0.5, 0.0   // Vértice 4
};

GLfloat colors[] = {
    1.0, 0.0, 0.0,  // Cor do vértice 1 (vermelho)
    0.0, 1.0, 0.0,  // Cor do vértice 2 (verde)
    0.0, 0.0, 1.0,  // Cor do vértice 3 (azul)
    1.0, 1.0, 0.0   // Cor do vértice 4 (amarelo)
};

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);   // Habilita o array de vértices
    glEnableClientState(GL_COLOR_ARRAY);    // Habilita o array de cores

    glVertexPointer(3, GL_FLOAT, 0, vertices);  // Define o ponteiro para o array de vértices
    glColorPointer(3, GL_FLOAT, 0, colors);    // Define o ponteiro para o array de cores

    glDrawArrays(GL_QUADS, 0, 4);  // Desenha o quadrado com 4 vértices

    glDisableClientState(GL_VERTEX_ARRAY);  // Desabilita o array de vértices
    glDisableClientState(GL_COLOR_ARRAY);   // Desabilita o array de cores

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL 11*Code - GL Client State - 12/11/2024 23:26");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
