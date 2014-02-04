

/**************************Author : JAVIER PANTA MARTINEZ ***********************************/



#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159265

int flag=1;

typedef float punto3f[3];
typedef float punto2f[2];

punto3f pos={12.5,5.0,0.0}; //posicion inicial de la nave, se va actualizando
float alfa=0.0;
float desv;
double t=0.0;

void suelo(int filas, int columnas)
{
	glColor3f(0.0, 1.0, 0.0);
	for(int j=0; j<filas; j++)
		for(int i=0; i<columnas; i++){
			glBegin(GL_LINE_LOOP);
			glVertex3i(i,0,-j);
			glVertex3i(i+1,0,-j);
			glVertex3i(i+1,0,-j-1);
			glVertex3i(i,0,-j-1);
			glEnd();
		}
}

void edificios( int ori, int num, float tam, float x, float z)
{	
	for(int i=0; i<num; i++)
	{
		punto3f vector={1.0, 2.0+sin(float(i)), 1.0};
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		if(ori)
			glTranslatef(x, (float)tam*vector[1]/2, z-((float)i*tam));
		else 
			glTranslatef(x+((float)i*tam), (float)tam*vector[1]/2, z);
		glScalef(vector[0],vector[1],vector[2]);		
		glutWireCube(tam);
		glPopMatrix();
	}
}

void nave(void)
{
	glRotatef(45.0, 0.0, -1.0, 0.0);
	glPushMatrix();
		glScalef(1.2, 1.0, 1.5);
		glutWireTetrahedron();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.2, 0.2, 0.2);
		glutWireSphere(0.2, 10, 8);
	glPopMatrix();
}

void mover(int direc, float vel)
{
	// variable direc indica la direccion del movimiento 0 = eje x, 1 = eje y, 2 = eje z. Vel = velocidad
	pos[direc]+=vel;
	if(direc==2){
		glLoadIdentity();
		gluLookAt (pos[0]-2.0, pos[1]+5.0, pos[2]+10.0, pos[0], pos[1], pos[2], 0.0, 1.0, 0.0);
	}
	else if(direc==0){
		glLoadIdentity();
		gluLookAt (pos[0]-5.0, pos[1]+10.0, pos[2]-2.0, pos[0], pos[1], pos[2], 0.0, 1.0, 0.0);
	}
	glPushMatrix();
	glTranslatef(pos[0], pos[1]+sin(pos[direc])/20, pos[2]);
	nave();
	glPopMatrix();
}

void giro(float dist, float vel, float ang)
{
	//la variable dist es la distancia al punto sobre el que se le aplicara el angulo de giro
	
	glLoadIdentity();
	gluLookAt (7.5, pos[1], -62.5, pos[0], pos[1], pos[2], 0.0, 1.0, 0.0);

	if(alfa<ang)
	{
		alfa+=vel;
		glPushMatrix();
			glTranslatef(pos[0]+dist, pos[1], pos[2]);//nuevo origen para el giro
			glPushMatrix();
				glRotatef(alfa, 0.0, -1.0, 0.0);
				glTranslatef(-dist, 0.0, 0.0); //coordenadas en q empezara giro respecto nuevo origen
				nave();
			glPopMatrix();
		glPopMatrix();
	}
	else //cuando termine de girar actualizar el vector posicion. Por ahora solo funciona en giros hacia -z y +x
	{
		pos[0]+=(dist-cos(ang*PI/180)*dist);
		pos[2]-=sin(ang*PI/180)*dist;
		alfa=0;
	}
}

/*void agitar_nave(void)
{
	glPushMatrix();	
	
	if(pos[0]>13.5)
	{
		flag=1;
		pos[0]-=desv/10;
		glTranslatef (pos[0], pos[1]+sin(hiper)/5, pos[2]);
	}
	else if(pos[0]<11.5)
	{
		flag=0;
		pos[0]+=desv/10;
		glTranslatef (pos[0], pos[1]+sin(hiper)/5, pos[2]);
	}
	else if(flag)
	{
		pos[0]-=desv;
		glTranslatef (pos[0], pos[1]+sin(hiper)/5, pos[2]);
	}
	else {
		pos[0]+=desv;
		glTranslatef (pos[0], pos[1]+sin(hiper)/5, pos[2]);
	}
	nave();
	glPopMatrix();
}*/