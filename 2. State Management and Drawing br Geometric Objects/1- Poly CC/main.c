#include <GL/glut.h>  // Biblioteca GLUT para janelas e eventos

// Função para desenhar um polígono convexo (quadrado)
void desenhaPoligonoConvexo(void) {
    // Desenhar um quadrado
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.8f);  // Vértice inferior esquerdo
        glVertex2f(-0.2f, -0.8f);  // Vértice inferior direito
        glVertex2f(-0.2f, -0.2f);  // Vértice superior direito
        glVertex2f(-0.8f, -0.2f);  // Vértice superior esquerdo
    glEnd();
}

// Função para desenhar um polígono não convexo (côncavo)
void desenhaPoligonoNaoConvexo(void) {
    // Desenhar uma forma côncava (estrela)
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.8f);   // Vértice superior
        glVertex2f(0.2f, 0.2f);   // Vértice inferior direito
        glVertex2f(0.8f, 0.2f);   // Ponto externo à direita
        glVertex2f(0.3f, -0.2f);  // Vértice interno inferior direito
        glVertex2f(0.5f, -0.8f);  // Ponto externo inferior
        glVertex2f(0.0f, -0.4f);  // Ponto interno inferior central
        glVertex2f(-0.5f, -0.8f); // Ponto externo inferior esquerdo
        glVertex2f(-0.3f, -0.2f); // Vértice interno inferior esquerdo
        glVertex2f(-0.8f, 0.2f);  // Ponto externo à esquerda
        glVertex2f(-0.2f, 0.2f);  // Vértice inferior esquerdo
    glEnd();
}



// Função de renderização
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa a tela

    // Desenhar o polígono convexo à esquerda
    //desenhaPoligonoConvexo();

    // Desenhar o polígono não convexo à direita
    desenhaPoligonoNaoConvexo();

    glFlush();  // Garante a execução dos comandos de desenho
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Inicializa GLUT
    glutCreateWindow("OpenGL 6*Code - Poly no Convex- 27/09/2024 22:59");  // Cria uma janela
    glutDisplayFunc(display);  // Função de renderização
    glutMainLoop();  // Loop de eventos
    return 0;
}
