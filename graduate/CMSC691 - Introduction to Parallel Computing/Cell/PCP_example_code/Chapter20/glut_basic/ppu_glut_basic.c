#include <GL/glut.h>

#define HEIGHT 300
#define WIDTH 300

/* function to be called for window display */
void display(void);

int main(int argc, char **argv){
 
   /* Initialize the window with the command-line arguments */
   glutInit(&argc, argv);
   
   /* Set the display mode to RGBA, single-buffered */
   glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
   
   /* Set the size to 300x300 pixels */
   glutInitWindowSize(WIDTH, HEIGHT);
   
   /* Position the window at (200, 100) */
   glutInitWindowPosition(200, 100);
   
   /* Create the window with a friendly title */
   glutCreateWindow("Hello GLUT!");
   
   /* Name the function to handle display events */
   glutDisplayFunc(display);
   
   /* Set the default color to white */
   glClearColor(1.0, 1.0, 1.0, 1.0);
   
   /* Start the processing loop */
   glutMainLoop();
   return 0;
}

void display(void) {

   /* Clear the window */
   glClear(GL_COLOR_BUFFER_BIT);
}
