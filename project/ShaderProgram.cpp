#include "ShaderProgram.hpp"

#define LOGFILE "log/ShaderDebuglog.txt"
#include <stdio.h>
#include <sstream>


//////////////////////////// SHADER ///////////////////////////////////////////////
ShaderProgram::ShaderProgram(const char *File,sf::Shader::Type Type)
{
    printLog("Creation du programme de shader");

    sf::Shader* shader=new sf::Shader();
    if (shader->LoadFromFile(File,Type))
    {
        std::stringstream out;
        out<<"ajout du shader "<<File<<" qui a le type "<<(sf::Shader::Type)Type;
        printLog(out.str());

        Tab_Shader.push_back(shader);
    }
    else
    {
        printLog(std::string("Imposible de lire le fichier, ou erreur dans le fichier ")+File);
        delete shader;
    }
};

ShaderProgram::ShaderProgram(const char *Vert,const char *Frag)
{
    printLog("Creation du programme de shader");
    sf::Shader* shader=new sf::Shader();

    if (shader->LoadFromFile(Vert,Frag))
    {
        std::stringstream out;
        out<<"ajout du shader chargeants les fichiers"<<Vert<<" et "<<Frag;
        printLog(out.str());

        Tab_Shader.push_back(shader);
    }
    else
    {
        printLog(std::string("Imposible de lire le fichier, ou erreur dans le fichier ")+Vert+ " ou le fichier "+Frag);
        delete shader;
    }
};

ShaderProgram::~ShaderProgram()
{
    printLog("Destruction du shader et des textures\n_________________________\n");

    for (int i=Tab_Shader.size()-1;i>=0;--i)
        delete Tab_Shader[i];

    for (int i=Tab_Texture.size()-1;i>=0;--i)
        delete Tab_Texture[i];
};


void ShaderProgram::printLog(std::string pbs)
{
    FILE *log=fopen(LOGFILE,"a");
    fprintf(log,"ShaderProgram: %s\n",pbs.c_str());
    fclose(log);
};


void ShaderProgram::setTexture(const char *nom,const char* Filename)
{
    sf::Texture* Texture = new sf::Texture();
    if(!Texture->LoadFromFile(Filename))
    {
        Texture->SetSmooth(true);
        printLog(std::string("Erreur de chargement du fichier ")+Filename);
        delete Texture;
    }
    else
    {
        Tab_Texture.push_back(Texture);
        for (int i=Tab_Shader.size()-1;i>=0;--i)
            Tab_Shader[i]->SetParameter(nom,*Texture);

    }
};

void ShaderProgram::setTexture(const char *nom,sf::Texture* Texture)
{
    Texture->SetSmooth(true);
    for (int i=Tab_Shader.size()-1;i>=0;--i)
        Tab_Shader[i]->SetParameter(nom,*Texture);
};


