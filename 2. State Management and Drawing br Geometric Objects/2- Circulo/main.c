#include <GL/glut.h>
#include <math.h>  // Para funções trigonométricas


// Função para desenhar um círculo usando aproximação por linhas
void desenhaCirculo(float raio, int numSegmentos) {
    glBegin(GL_LINE_LOOP);  // Inicia a linha fechada (aproximação do círculo)
    for (int i = 0; i < numSegmentos; i++) {
        float angulo = 2.0f * 3.14 * i / numSegmentos;  // Ângulo em radianos
        float x = raio * cos(angulo);  // Coordenada X
        float y = raio * sin(angulo);  // Coordenada Y
        glVertex2f(x, y);  // Define o vértice na posição calculada
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa a tela

    // Desenha um círculo com 100 segmentos (aproximação razoável)
    desenhaCirculo(0.5f, 100);

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL 7*Code - Circule Line Curves - 27/09/2024 23:09");
    glutDisplayFunc(display);  // Função de renderização
    glutMainLoop();
    return 0;
}
