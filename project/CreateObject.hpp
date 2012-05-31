#ifndef CREATOBJECT_HPP
#define CREATOBJECT_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include <cmath>



#define Box(x,y,z)\
{\
	glPushMatrix();\
	glScalef(x,y,z);\
	glBegin (GL_QUADS);\
	glNormal3i(-1, 1,-1);\
	glVertex3i(-1, 1,-1); glVertex3i( 1, 1,-1);\
	glVertex3i( 1,-1,-1); glVertex3i(-1,-1,-1);\
	\
	glNormal3i(-1,-1,-1);\
	glVertex3i(-1,-1,-1); glVertex3i( 1,-1,-1);\
	glVertex3i( 1,-1, 1); glVertex3i(-1,-1, 1);\
	\
	glNormal3i( 1,-1, 1);\
	glVertex3i( 1,-1, 1); glVertex3i( 1,-1,-1);\
	glVertex3i( 1, 1,-1); glVertex3i( 1, 1, 1);\
	\
	glNormal3i( 1, 1,-1);\
	glVertex3i( 1, 1,-1); glVertex3i(-1, 1,-1);\
	glVertex3i(-1, 1, 1); glVertex3i( 1, 1, 1);\
	\
	glNormal3i(-1, 1, 1);\
	glVertex3i(-1, 1, 1); glVertex3i(-1, 1,-1);\
	glVertex3i(-1,-1,-1); glVertex3i(-1,-1, 1);\
	\
	glNormal3i( 1,-1, 1);\
	glVertex3i( 1,-1, 1); glVertex3i( 1, 1, 1);\
	glVertex3i(-1, 1, 1); glVertex3i(-1,-1, 1);\
	glEnd();\
	glPopMatrix();\
}
float deg2rad(float deg) {
    return deg*M_PI/180.0f;
};

/*
static GLuint MkSphere(int segmentsH, int segmentsV, GLfloat Kd[])
    // crée une liste d'affichage dessinant une sphère de rayon 1, centrée en 0,0,0
    // cette sphère est générée avec les nombres de facettes en longitude et latitude
{
    // réserver et créer une liste d'affichage
    static GLuint listeAffichage = glGenLists(1);
    glNewList(listeAffichage, GL_COMPILE);

    //// matériau pour les polygones
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kd);
	GLfloat Kblanc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, Kblanc);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    //// création des polygones
    int dlon=segmentsH/10;
    int dlat=segmentsV/10;
    float lon, lat;

    float latr, lonr, x, y, z;

    for(lat=-90; lat<=90; lat+=dlat) {
        glBegin(GL_QUAD_STRIP);
        for (lon=0; lon<=360; lon+=dlon) {
            latr = deg2rad(lat);
            lonr = deg2rad(lon);

            x=cos(latr)*sin(lonr);
            y=sin(latr);
            z=cos(latr)*cos(lonr);
            glColor3f((sin(lonr)+1)/2, (cos(lonr)+1)/2, (sin(latr)+1)/2);
            glTexCoord2f(lon/360, (lat+90)/180); glNormal3f(x, y, z); glVertex3f(x, y, z);

            latr = deg2rad(lat+dlat);
            x=cos(latr)*sin(lonr);
            y=sin(latr);
            z=cos(latr)*cos(lonr);
            glColor3f((sin(lonr)+1)/2, (cos(lonr)+1)/2, (sin(latr)+1)/2);
            glTexCoord2f(lon/360, (lat+90)/180); glNormal3f(x, y, z); glVertex3f(x, y, z);
        }

    }
    glEnd();


    // la liste est finie, on retourne son numéro
    glEndList();
    return listeAffichage;
};
*/
static GLuint MKBox()
{
    // réserver et créer une liste d'affichage
    static GLuint listeAffichage = 0;
    if (listeAffichage ==0)
    {
        listeAffichage= glGenLists(1);
        glNewList(listeAffichage, GL_COMPILE);
        glBegin (GL_QUADS);

            glNormal3i(-1, 1,-1);
            glTexCoord2f(0, 1); glVertex3i(-1, 1,-1);
            glTexCoord2f(1, 1); glVertex3i( 1, 1,-1);
            glTexCoord2f(1, 0); glVertex3i( 1,-1,-1);
            glTexCoord2f(0, 0); glVertex3i(-1,-1,-1);

            glNormal3i(-1,-1,-1);
            glTexCoord2f(0, 0); glVertex3i(-1,-1,-1);
            glTexCoord2f(1, 0); glVertex3i( 1,-1,-1);
            glTexCoord2f(1, 1); glVertex3i( 1,-1, 1);
            glTexCoord2f(0, 1); glVertex3i(-1,-1, 1);

            glNormal3i( 1,-1, 1);
            glTexCoord2f(0, 1); glVertex3i( 1,-1, 1);
            glTexCoord2f(0, 0); glVertex3i( 1,-1,-1);
            glTexCoord2f(1, 0); glVertex3i( 1, 1,-1);
            glTexCoord2f(1, 1); glVertex3i( 1, 1, 1);

            glNormal3i( 1, 1,-1);
            glTexCoord2f(1, 0); glVertex3i( 1, 1,-1);
            glTexCoord2f(0, 0); glVertex3i(-1, 1,-1);
            glTexCoord2f(0, 1); glVertex3i(-1, 1, 1);
            glTexCoord2f(1, 1); glVertex3i( 1, 1, 1);

            glNormal3i(-1, 1, 1);
            glTexCoord2f(1, 1); glVertex3i(-1, 1, 1);
            glTexCoord2f(1, 0); glVertex3i(-1, 1,-1);
            glTexCoord2f(0, 0); glVertex3i(-1,-1,-1);
            glTexCoord2f(0, 1); glVertex3i(-1,-1, 1);

            glNormal3i( 1,-1, 1);
            glTexCoord2f(1, 0); glVertex3i( 1,-1, 1);
            glTexCoord2f(1, 1); glVertex3i( 1, 1, 1);
            glTexCoord2f(0, 1); glVertex3i(-1, 1, 1);
            glTexCoord2f(0, 0); glVertex3i(-1,-1, 1);
        glEnd();
        // la liste est finie, on retourne son numéro
        glEndList();
    }
    return listeAffichage;
};

/*
GLuint MakePyramide(void)
{
    // créer une liste
    GLuint liste = glGenLists(1);
    if (!liste) return liste;       // y a un couac !

    // démarrer l'enregistrement
    glNewList(liste, GL_COMPILE);

    // base
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);  glVertex3f(-1.0f,0.0f,-1.0f);   // rouge
    glColor3f(1.0f,1.0f,0.0f);  glVertex3f(-1.0f,0.0f,+1.0f);   // jaune
    glColor3f(0.0f,1.0f,1.0f);  glVertex3f(+1.0f,0.0f,+1.0f);   // cyan
    glColor3f(1.0f,0.0f,1.0f);  glVertex3f(+1.0f,0.0f,-1.0f);   // magenta
    glEnd();
    printOpenGLError();

    // cotés
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f,1.0f,0.0f);  glVertex3f(0.0f,2.0f,0.0f);     // vert
    glColor3f(1.0f,0.0f,0.0f);  glVertex3f(-1.0f,0.0f,-1.0f);   // rouge
    glColor3f(1.0f,0.0f,1.0f);  glVertex3f(+1.0f,0.0f,-1.0f);   // magenta
    glColor3f(0.0f,1.0f,1.0f);  glVertex3f(+1.0f,0.0f,+1.0f);   // cyan
    glColor3f(1.0f,1.0f,0.0f);  glVertex3f(-1.0f,0.0f,+1.0f);   // jaune
    glColor3f(1.0f,0.0f,0.0f);  glVertex3f(-1.0f,0.0f,-1.0f);   // rouge
    glEnd();

    // fin de l'enregistrement
    glEndList();

    return liste;
}

GLuint MakeTore(float r, int dlon, int dlat)
{
    // créer une liste
    GLuint liste = glGenLists(1);
    if (!liste) return liste;       // y a un couac !

    // démarrer l'enregistrement
    glNewList(liste, GL_COMPILE);

    // à vous de le faire !
    float lon, lat;
    int R=1;

    for (lon=0; lon<360; lon+=dlon) {
        glBegin(GL_QUAD_STRIP);
        for (lat=0; lat<360; lat+=dlat) {
            float x=( R + r*cos(deg2rad(lat)) ) * cos(deg2rad(lon));
            float y=r*sin(deg2rad(lat));
            float z=( R + r*cos(deg2rad(lat)) ) * sin(deg2rad(lon));
            glColor3f(sin(deg2rad(lon)+1), cos(deg2rad(lon)+1), sin(deg2rad(lat)+1)); glVertex3f(x, y, z);

            x=( R + r*cos(deg2rad(lat)) ) * cos(deg2rad(lon+dlon));
            z=( R + r*cos(deg2rad(lat)) ) * sin(deg2rad(lon+dlon));
            glVertex3f(x, y, z);
        }
        glEnd();
    }


    // fin de l'enregistrement
    glEndList();

    return liste;
}

GLuint MakeRessort(float n, float pas, float r, int dlon, int dlat)
{
    // créer une liste
    GLuint liste = glGenLists(1);
    if (!liste) return liste;       // y a un couac !

    // démarrer l'enregistrement
    glNewList(liste, GL_COMPILE);

    float lon, lat;
    int R=1;

    for (lon=0; lon<360*n; lon+=dlon) {
        glBegin(GL_QUAD_STRIP);
        for (lat=0; lat<360; lat+=dlat) {
            float x=( R + r*cos(deg2rad(lat)) ) * cos(deg2rad(lon));
            float y=r*sin(deg2rad(lat))+r*pas*lon/360;
            float z=( R + r*cos(deg2rad(lat)) ) * sin(deg2rad(lon));
            glColor3f(sin(deg2rad(lon)+1), cos(deg2rad(lon)+1), sin(deg2rad(lat)+1)); glVertex3f(x, y, z);

            x=( R + r*cos(deg2rad(lat)) ) * cos(deg2rad(lon+dlon));
            z=( R + r*cos(deg2rad(lat)) ) * sin(deg2rad(lon+dlon));
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    // fin de l'enregistrement
    glEndList();

    return liste;
}

GLuint MakeCoquille(float n, float pas, float r, int dlon, int dlat)
{
    // créer une liste
    GLuint liste = glGenLists(1);
    if (!liste) return liste;       // y a un couac !

    // démarrer l'enregistrement
    glNewList(liste, GL_COMPILE);

    // à vous de le faire !
    float lon, lat;
    int R=1;
    float Rprime, rprime, K=0.5, k=1.0;

    for (lon=0; lon<360*n; lon+=dlon) {
        glBegin(GL_QUAD_STRIP);
        Rprime=R*lon/360*K;
        rprime=r*lon/360*k;

        for (lat=0; lat<360; lat+=dlat) {
            float x=( Rprime + rprime*cos(deg2rad(lat)) ) * cos(deg2rad(lon));
            float y=rprime*sin(deg2rad(lat));
            float z=( Rprime + rprime*cos(deg2rad(lat)) ) * sin(deg2rad(lon));
            glColor3f(sin(deg2rad(lon)+1), cos(deg2rad(lon)+1), sin(deg2rad(lat)+1)); glVertex3f(x, y, z);

            x=( Rprime + rprime*cos(deg2rad(lat)) ) * cos(deg2rad(lon+dlon));
            z=( Rprime + rprime*cos(deg2rad(lat)) ) * sin(deg2rad(lon+dlon));
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    // fin de l'enregistrement
    glEndList();

    return liste;
}

GLuint MakeRubanMoebius(int n, float r, int dlon)
{
    // créer une liste
    GLuint liste = glGenLists(1);
    if (!liste) return liste;       // y a un couac !

    // démarrer l'enregistrement
    glNewList(liste, GL_COMPILE);
    int lon, lat;
    float Rp, rp, K=0.5, k=1.0;

    glBegin(GL_QUAD_STRIP);

    for(lon=0; lon<360; lon+=dlon) {
            Rp=1*lon/360*K;
            r=r*lon/360*k;
            lat=lon*n/2;
            float x=(Rp+rp*cos(deg2rad(lat)))*cos(deg2rad(lon));
            float y=rp*sin(deg2rad(lat))+rp*3*lon/360;
            float z=(Rp+rp*cos(deg2rad(lat)))*sin(deg2rad(lon));
            glColor3f(sin(deg2rad(lon)+1), cos(deg2rad(lon)+1), sin(deg2rad(lat)+1)); glVertex3f(x, y, z);
    }
    glEnd();
    // fin de l'enregistrement
    glEndList();

    return liste;
}
*/
#endif
