#include "ShaderProgram.hpp"

#define LOGFILE "log/ShaderDebuglog.txt"

char *TextFileRead(const char *nomfich)
{
    // ouvrir le fichier en mode texte
    FILE *fich = fopen(nomfich,"rt");
    if (!fich) return NULL;

    // obtenir la taille du fichier
    fseek(fich, 0, SEEK_END);
    int taille = ftell(fich);
    rewind(fich);

    // lire le contenu
    char *contenu = NULL;
    if (taille > 0) {
        // allouer de la mémoire pour le contenu
        contenu = (char*)malloc(taille + 1);
        taille = fread(contenu,sizeof(char),taille,fich);
        contenu[taille] = '\0';
    }
    fclose(fich);
    return contenu;
};
//////////////////////////// SHADER ///////////////////////////////////////////////
ShaderProgram::ShaderProgram(const char *vertex, const char *fragment)
{
    vertexShader   = CompileSource(vertex, GL_VERTEX_SHADER);
    fragmentShader = CompileSource(fragment, GL_FRAGMENT_SHADER);
    // création du programme complet regroupant les deux shaders
    Program = glCreateProgram();
    if (vertexShader)   glAttachShader(Program,vertexShader);
    if (fragmentShader) glAttachShader(Program,fragmentShader);

    glLinkProgram(Program);
    printProgramInfoLog(Program);

    {
        FILE *log=fopen(LOGFILE,"a");
        fprintf(log,"ShaderProgram: construction du shader ok (id=%d).\n",Program);
        fclose(log);
    }
};

ShaderProgram::~ShaderProgram()
{
    glDetachShader(Program, vertexShader);
    glDeleteShader(vertexShader);
    vertexShader = 0;

    glDetachShader(Program, fragmentShader);
    glDeleteShader(fragmentShader);
    fragmentShader = 0;

    glDeleteProgram(Program);
    Program = 0;
    {
        FILE *log=fopen(LOGFILE,"a");
        fprintf(log,"ShaderProgram: destruction du shader ok.\n");
        fclose(log);
    }
};


GLuint ShaderProgram::CompileSource(const char *nomfichier, int type)
{
    if (!nomfichier)
        return 0;

    // créer un shader du type demandé
    GLuint shader = glCreateShader(type);

    // lecture du fichier source
    char *contenu = TextFileRead(nomfichier);
    if (contenu)
    {
        // fournir le contenu du fichier au GPU pour qu'il puisse le compiler
        glShaderSource(shader, 1, (const GLchar**)&contenu,NULL);

        // libérer la mémoire occupée par le contenu
        free(contenu);
    }
    else
    {
        // on a fourni un source GLSL au lieu d'un nom de fichier
        glShaderSource(shader, 1, (const GLchar**)&nomfichier,NULL);
    }

    // compilation du source et affichage des erreurs
    glCompileShader(shader);
    if (contenu)
        printShaderInfoLog(shader, nomfichier);
    else
        printShaderInfoLog(shader, "source inclus");

    return shader;
};

void ShaderProgram::printShaderInfoLog(GLuint obj, const char *nom)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        {
            FILE *log=fopen(LOGFILE,"a");
            fprintf(log,"ShaderProgram: in %s, %s\n",nom,infoLog);
            fclose(log);
        }
        free(infoLog);
    }
};

void ShaderProgram::printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        {
            FILE *log=fopen(LOGFILE,"a");
            fprintf(log,"ShaderProgram: %s\n",infoLog);
            fclose(log);
        }
        free(infoLog);
    }
};


static unsigned int NumeroTexture=0;

#include <iostream>
void ShaderProgram::setTexture(const char *nom,const char* Filename)
{
    sf::Image image;

    if (! image.LoadFromFile(Filename))
        return;
    glUseProgram(Program);


    GLuint numeroGL = NumeroTexture;
    glGenTextures(NumeroTexture, &numeroGL);
    glBindTexture(GL_TEXTURE_2D, numeroGL);

    //image.Bind();
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.CopyToImage().GetPixelsPtr());
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glActiveTexture(GL_TEXTURE0 + NumeroTexture);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, numeroGL);

    GLint loc = glGetUniformLocation(Program, nom);
    if (loc == -1)
    {
        FILE *log=fopen(LOGFILE,"a");
        fprintf(log,"ShaderProgram: uniform sampler2D \"%s\" est inconnue ou inutilisee.\n",nom);
        fclose(log);
    }
    else
    {
        glUniform1i(loc, NumeroTexture);
    }
    // réactiver l'unité par défaut
    glUseProgram(0);
    glActiveTexture(GL_TEXTURE0);


    ++NumeroTexture;
};

/*void ShaderProgram::LoadTexturesFromFile(const char *filename)
{
    setTexture("truc",new sf::Image(filename));
}*/
