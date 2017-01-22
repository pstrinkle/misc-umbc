#include <GL/glut.h>

#define HEIGHT 300
#define WIDTH 300

/* Initialize the OpenGL state matrices */
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2, 20.0);
   glMatrixMode(GL_MODELVIEW);
}

/* Draw the three spheres */
void display(void) {
   /* Clear the window */
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0, 0);      
   glLoadIdentity();
   
   /* Draw the first sphere */
   glTranslatef(-1, -1, -4);
   glutWireSphere(1.0, 10, 10);
   
   /* Draw the second sphere */
   glTranslatef(2, 2, -4);
   glutWireSphere(1.0, 10, 10);   
   
   /* Draw the second sphere */
   glTranslatef(3, 3, -4);
   glutWireSphere(1.0, 10, 10);   
   
   glutSwapBuffers();
}

int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize(WIDTH, HEIGHT);
   glutInitWindowPosition(200, 100);
   glutCreateWindow("Spheres in a Frustum");
   init();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
