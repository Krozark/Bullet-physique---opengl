#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include <SFML/Graphics.hpp>
#include <bullet/LinearMath/btVector3.h>
#include <map>
#include <string>

class Fenettre;
#include "Fenettre.hpp"

class FreeFlyCamera
{
    public:
        FreeFlyCamera(const btVector3 & position = btVector3(0,0,0));

        void MouseMoved();
        void MouseWheelMoved(const sf::Event & event);

        void animate(double timestep);
        inline void setSpeed(double speed){Speed = speed;};
        inline void setSensivity(double sensivity){Sensibilitee_souris = sensivity;};
        inline void setPosition(const btVector3 & position){Position = position;Cible_vision = Position + Avent;};
        inline btVector3 GetPosition(){return Position;};
        inline btVector3 GetCible(){return Cible_vision;};

        inline void look(){gluLookAt(Position[0],Position[1],Position[2],Cible_vision[0],Cible_vision[1],Cible_vision[2],0,1,0);};

        ~FreeFlyCamera();
    protected:
        double Speed;
        double Sensibilitee_souris;

        //vertical motion stuffs
        double _timeBeforeStoppingVerticalMotion;
        bool _verticalMotionActive;
        int _verticalMotionDirection;

        std::map<std::string,sf::Keyboard::Key> KeyConf;

        btVector3 Position;
        btVector3 Cible_vision;
        btVector3 Avent;
        btVector3 Droite;
        double Theta;
        double Phi;

        void VectorsFromAngles();
        //void Init();
};

#endif //FREEFLYCAMERA_H
