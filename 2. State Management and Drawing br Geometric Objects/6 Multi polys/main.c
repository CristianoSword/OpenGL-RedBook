#include <GL/freeglut.h>

float vertices[] = {
    // Posição
    0.0f,  0.5f, 0.0f,  // Vértice 0
    -0.5f, -0.5f, 0.0f, // Vértice 1
    0.5f, -0.5f, 0.0f,  // Vértice 2
};

float colors[] = {
    // Cor (R, G, B)
    1.0f, 0.0f, 0.0f, // Vermelho
    0.0f, 1.0f, 0.0f, // Verde
    0.0f, 0.0f, 1.0f, // Azul
};

float texCoords[] = {
    // Coordenadas de textura
    0.0f, 1.0f, // Vértice 0
    1.0f, 1.0f, // Vértice 1
    0.5f, 0.0f, // Vértice 2
};

GLuint vbo[3]; // VBOs para vértices, cores e coordenadas de textura
GLuint vao;    // VAO para agrupar os VBOs

int stride = sizeof(float) * 3; // Tamanho do passo para os atributos de vértices

// Função de display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Habilita os arrays de vértices, cores e coordenadas de textura
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Define os ponteiros dos atributos
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0); // Ponteiro para os vértices

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glColorPointer(3, GL_FLOAT, 0, (void*)0); // Ponteiro para as cores

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, (void*)0); // Ponteiro para as coordenadas de textura

    // Desenha o triângulo
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Desabilita os arrays após o desenho
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

// Função de inicialização
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo (preto)

    // Gerar e vincular os VBOs
    glGenBuffers(3, vbo);

    // VBO para vértices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // VBO para cores
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // VBO para coordenadas de textura
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    // Criar e vincular o VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

// Função de redimensionamento da janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Define a área de exibição
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define uma projeção ortográfica
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Freeglut Example");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
