#include <GL/glut.h>
#include <stdlib.h>

static float angle = 0.0; // Ângulo de rotação em torno do eixo Y

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0); // Cor de fundo: preto
   glShadeModel(GL_FLAT);            // Sombreamento sem gradiente
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0); // Cor do cubo: branco
   
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 2.5,   // Posição fixa da câmera
             0.0, 0.0, 0.0,   // Ponto para onde a câmera olha
             0.0, 1.0, 0.0);  // Vetor "para cima"

   glRotatef(angle, 0.0, 1.0, 0.0); // Rotação ao redor do eixo Y
   glutWireCube(1.0);               // Desenha o cubo

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // Projeção em perspectiva
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: // ESC
         exit(0);
         break;
   }
}

void timer(int value)
{
   angle += 1.3; // Incrementa o ângulo de rotação
   if (angle >= 360.0) angle -= 360.0; // Mantém o ângulo dentro de [0, 360)
   glutPostRedisplay(); // Solicita redesenho da janela
   glutTimerFunc(16, timer, 0); // Chama a si mesmo após 16 ms (~60 FPS)
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL 15*Code - Camera Cube Rotation - 18/11/2024 22:51");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(16, timer, 0); // Inicia o temporizador
   glutMainLoop();
   return 0;
}



