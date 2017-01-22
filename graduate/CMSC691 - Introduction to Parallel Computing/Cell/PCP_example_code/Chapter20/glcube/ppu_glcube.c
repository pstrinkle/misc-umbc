#include <GL/glut.h>

#define HEIGHT 300
#define WIDTH 300

/* Faces of the cube */
short topFace[4][3] =    { { 1, 1,-1},  {-1, 1,-1},  {-1, 1, 1},   { 1, 1, 1} };
short bottomFace[4][3] = { { 1,-1, 1},  {-1,-1, 1},  {-1,-1,-1},   { 1,-1,-1} };
short frontFace[4][3] =  { { 1, 1, 1},  {-1, 1, 1},  {-1,-1, 1},   { 1,-1, 1} };
short backFace[4][3] =   { { 1,-1,-1},  {-1,-1,-1},  {-1, 1,-1},   { 1, 1,-1} };
short leftFace[4][3] =   { {-1, 1, 1},  {-1, 1,-1},  {-1,-1,-1},   {-1,-1, 1} };
short rightFace[4][3] =  { { 1, 1,-1},  { 1, 1, 1},  { 1,-1, 1},   { 1,-1,-1} };

/* Initialize the OpenGL state matrices */
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 2, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_CULL_FACE);
}

/* Draw the cube */
void display(void) {
   int i;
   
   /* Clear the window */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   
   /* Position cube in the region and rotate */
   glTranslatef(0, 0, -7);
   glRotatef(30, 1, 1, 1);

   glBegin(GL_QUADS);
      
      /* Color the top face red */
      glColor3f(1, 0, 0);
      glVertex3sv(topFace[0]);
      glVertex3sv(topFace[1]);
      glVertex3sv(topFace[2]);
      glVertex3sv(topFace[3]);    

      /* Color the bottom face green */
      glColor3f(0, 1, 0);
      glVertex3sv(bottomFace[0]);
      glVertex3sv(bottomFace[1]);
      glVertex3sv(bottomFace[2]);
      glVertex3sv(bottomFace[3]);          

      /* Color the front face blue */      
      glColor3f(0, 0, 1);
      glVertex3sv(frontFace[0]);
      glVertex3sv(frontFace[1]);
      glVertex3sv(frontFace[2]);
      glVertex3sv(frontFace[3]);    

      /* Color the back face yellow */        
      glColor3f(1, 1, 0);
      glVertex3sv(backFace[0]);
      glVertex3sv(backFace[1]);
      glVertex3sv(backFace[2]);
      glVertex3sv(backFace[3]); 

      /* Color the left face fuchsia */      
      glColor3f(1, 0, 1);
      glVertex3sv(leftFace[0]);
      glVertex3sv(leftFace[1]);
      glVertex3sv(leftFace[2]);
      glVertex3sv(leftFace[3]);       
         
      /* Color the right face aqua */          
      glColor3f(0, 1, 1);
      glVertex3sv(rightFace[0]);
      glVertex3sv(rightFace[1]);
      glVertex3sv(rightFace[2]);
      glVertex3sv(rightFace[3]);       
         
   glEnd();   
   glutSwapBuffers();
}

/*  Main Loop
 */
int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize(WIDTH, HEIGHT);
   glutInitWindowPosition(200, 100);
   glutCreateWindow("Color Cube");
   init();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
