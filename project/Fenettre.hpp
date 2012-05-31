#ifndef WORLD_HPP
#define WORLD_HPP

///     OPEN GL
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glx.h>
///     BULLET
#include <bullet/btBulletDynamicsCommon.h>
///     SFML
#include <SFML/Window.hpp>
///     STL
#include <iostream>
#include <sstream>
///     PERSO
#include "Object.hpp"

///     CONSTANTES
#define FRAME_TIME  30

class FreeFlyCamera;

inline int randRange2i(int fMin, int fMax)
{
    return fMin +rand()%fMax;
};

inline double randRange2d(double fMin, double fMax)
{
    return fMin + ((double)rand() / RAND_MAX)*(fMax - fMin);
};


class Fenettre : public sf::Window
{
    public:
        Fenettre (sf::VideoMode Mode,std::string nom,float FrameTime=FRAME_TIME);
        Fenettre ();
        ~Fenettre();

        void AddRigidBox(btVector3 position,btScalar mass,btVector3 size=btVector3(1,1,1));
        void RenderScene();
        void RenderMe();
        void PositionCamera();
    private:
        ///Bullet Config
        btDefaultCollisionConfiguration* CollisionConfiguration;
        btCollisionDispatcher* Dispatcher;
        btBroadphaseInterface* Broadphase;
        btSequentialImpulseConstraintSolver* SequentialImpulseConstraintSolver;
        btDiscreteDynamicsWorld* World;

        btStaticPlaneShape* Terrain;

        ///Perso
        btAlignedObjectArray<RigideObject*> ObjetsBt;
        FreeFlyCamera* camera;

        void Init();
        void shootBox(const btVector3& destination);

};

#endif
