

/**************************Author : JAVIER PANTA MARTINEZ ***********************************/



#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <GL/glut.h>
#include "city.h"

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void movimiento(void){
	if(pos[1]>150) {pos[0]=12.5; pos[1]=5.0; pos[2]=0.0; t=0.0;} //loop
	glutPostRedisplay();

}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	//gluLookAt (10.0, 7.0, 10.0, 12.5, 7.0, 0.0, 0.0, 1.0, 0.0); //camara en movimiento, si usas esto quita la otra q esta en reshape
	suelo(80,80);
	edificios(1, 13, 5.0, 5.0, -5.0); //orientacion, numero de edifios, ancho, posicion en plano (x,z)
	edificios(1, 10, 5.0, 20.0, -5.0);
	edificios(0, 10, 5.0, 25.0, -50.0);
	edificios(0, 13, 5.0, 10.0, -65.0);
	//gluLookAt (10.0, 7.0, 10.0, 12.5, 7.0, 0.0, 0.0, 1.0, 0.0);
	if(pos[2]>-50.0)
		mover(2, (-0.2)); //la velocidad negativa para q se mueva hacia -z
	else 
		if(pos[2]<-50.0 && pos[2]>-50.3)//punto de la curva, la velocidad hace q no sea un punto exacto.
			giro(7.5, 1.0, 90.0);
		else 
			if(pos[0]<70)
				mover(0, 0.2);
			else 
			{
				pos[0]+=0.2; t+=0.01; pos[1]+=pow(t,2.0); //salto al hiperespacio (pow es funcion exponencial de t)

				glLoadIdentity();
				gluLookAt (70, 5.0+10.0, pos[2]-2.0, pos[0], pos[1], pos[2], 0.0, 1.0, 0.0);

				glPushMatrix();
				glTranslatef(pos[0], pos[1], pos[2]);
				nave();
				glPopMatrix();
			}
	glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   /* inicializa la proyección: */
   /* campo de visión, razón de aspecto, plano delantero y trasero */
   gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   /* Situa la cámara: posición, hacia donde apunta, vector up */
   //gluLookAt (20.0, 20.0, 0.0, 20.0, 15.0, -40.0, 0.0, 1.0, 0.0);
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutIdleFunc(movimiento);
   glutMainLoop();	
   return 0;
}
