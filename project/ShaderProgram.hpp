#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class ShaderProgram
{

    public :
        ShaderProgram(const char *File,sf::Shader::Type Type);
        ShaderProgram(const char *Vert,const char *Frag);
        ~ShaderProgram();

        inline void Bind(){for(int i = Tab_Shader.size()-1;i>=0;--i)Tab_Shader[i]->Bind();};
        inline void Unbind(){for(int i = Tab_Shader.size()-1;i>=0;--i)Tab_Shader[i]->Unbind();};

        void setTexture(const char *nom,const char* Filename);
        void setTexture(const char *nom,sf::Texture* Texture);
        inline void setTexture(const char* nom){for(int i = Tab_Shader.size()-1;i>=0;--i)Tab_Shader[i]->SetParameter(nom, sf::Shader::CurrentTexture);};

    private :
        // affichage d'informations de compilation dans log.txt
        std::vector<sf::Texture*> Tab_Texture;
//        std::vector< pair<sf::Shader, int Type> > Tab_Shaders;
        std::vector<sf::Shader*> Tab_Shader;
        void printLog(std::string pbs);
};
#endif
