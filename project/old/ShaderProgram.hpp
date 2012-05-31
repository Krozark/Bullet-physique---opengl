#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class ShaderProgram
{

    public :
        ShaderProgram(const char *vertex=NULL, const char *fragment=NULL);
        ~ShaderProgram();

        inline void SetUsabled(bool use){if(use)glUseProgram(Program);else glUseProgram(0);};
        inline void UseMe(){glUseProgram(Program);};
        inline void DontUseMe(){glUseProgram(0);};

        void setTexture(const char *nom,const char* Filename);
        //void LoadTexturesFromFile(const char *filename);

    protected:
        GLuint Program,vertexShader,fragmentShader;

    private :
        GLuint CompileSource(const char *nomfichier, int type);
        // affichage d'informations de compilation dans log.txt
        void printShaderInfoLog(GLuint obj, const char *nom);
        void printProgramInfoLog(GLuint obj);
};
#endif
