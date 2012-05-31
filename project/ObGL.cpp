#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ObGL.hpp"



//lecture du fichier obj

GLuint LireFichierObj(const char *nomfichierobj)
{
    // tableau des points
    struct Vertex
    {
        float x,y,z;
    } *TabVertex;
    // nombre de points placés dans le tableau
    int NbVertex;
    // nombre maximal de points qu'on peut mettre
    int TailleTabVertex;

    // initialisation du tableau
    NbVertex = 0;
    TailleTabVertex = 100;
    TabVertex = (struct Vertex*)malloc(TailleTabVertex * sizeof(struct Vertex));

    // création de la liste d'affichage de l'objet
    GLuint la_ObjetLu = glGenLists(1);
    glNewList(la_ObjetLu, GL_COMPILE);

    // couleur par défaut des points
    float r = 1.0,v = 1.0, b = 1.0;
    glColor3f(r,v,b);

    // ouverture du fichier .obj
    FILE *fichier = fopen(nomfichierobj, "r");
    if (!fichier) exit(1);

    // parcours et traitement de toutes ses lignes
    char *ligne= new char[81];
    while (fgets(ligne,80,fichier))
    {
        // extraire le premier mot de la ligne
        char *mot = strtok(ligne," ");

        // comparer le premier mot de la ligne avec v, vt, vn, f, usemtl, mtllib...
        if (strcmp(mot,"v") == 0)
        {
            // agrandir le tableau des vertices ?
            if (NbVertex >= TailleTabVertex)
            {
                TailleTabVertex += 100;
                TabVertex = (struct Vertex*)realloc(TabVertex,
                    TailleTabVertex * sizeof(struct Vertex));
            }
            // obtenir les trois coordonnées du vertex
            float x,y,z;
            mot = strtok(ligne, " "); sscanf(mot,"%f",&x);
            mot = strtok(ligne, " "); sscanf(mot,"%f",&y);
            mot = strtok(ligne, " "); sscanf(mot,"%f",&z);
            // enregistrer le point x,y,z dans le tableau des vertices
//            #warning "pas fait et en plus il y a un bug quelque part"
        }
        else if (strcmp(mot,"f") == 0)
        {
            // démarrer un polygone

            while ((mot = strtok(ligne," ")))
            {
                // extraire les trois numéros (dont 2 en option)
                int numv=0, numvt=0, numvn=0;
                sscanf(mot,"%d/%d/%d",&numv,&numvt,&numvn);
                // ajouter le vertex numv-1 sauf si pb avec numv
                if (numv < 1 || numv > NbVertex)
                    continue; // ignorer ce point
             //   #warning "pas fait et en plus il y a un bug quelque part"

            }
            // fin du polygone
        }
        else      // ajout PN à la norme .obj, pour avoir des couleurs
        if (strcmp(mot,"color") == 0)
        {
            // changer la couleur courante (PAS STANDARD !!)
            mot = strtok(NULL, " "); sscanf(mot,"%f",&r);
            mot = strtok(NULL, " "); sscanf(mot,"%f",&v);
            mot = strtok(NULL, " "); sscanf(mot,"%f",&b);
            glColor3f(r,v,b);
        }
    }
    glEndList();

    fclose(fichier);

    delete ligne;
    delete TabVertex;

    return la_ObjetLu;
};
