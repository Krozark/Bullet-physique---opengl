#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <bullet/btBulletDynamicsCommon.h>
#include "ShaderProgram.hpp"

/// TODO Rendre le Shape Static
class Object
{
    public:
        Object(float mass,btDiscreteDynamicsWorld* World,btVector3 position);
        ~Object();
        inline btCollisionShape* GetShape(){return Shape;};
        inline btDefaultMotionState* GetMotionState(){return MotionState;};
        virtual void DrawGL() =0;
        inline void SetShaderProgram(ShaderProgram* P){Program = P;};
        inline ShaderProgram* GetShaderProgram(){return Program;};
    protected:
        float mass;
        btDefaultMotionState * MotionState;
        btCollisionShape* Shape;
        ShaderProgram* Program;
};

class RigideObject : public Object
{
    public:
        RigideObject(float mass,btDiscreteDynamicsWorld* World,btVector3 position);
        ~RigideObject();
        virtual void DrawGL() =0;

        inline void setLinearFactor(const btVector3& v){body->setLinearFactor(v);};
        inline void setOrigin(const btVector3& pos){body->getWorldTransform().setOrigin(pos);};
        inline void setRotation(const btQuaternion& r){body->getWorldTransform().setRotation(r);};
        inline void setLinearVelocity(const btVector3& v){body->setLinearVelocity(v);};
        inline void setAngularVelocity(const btVector3& v){body->setAngularVelocity(v);};
        inline void setCcdMotionThreshold(const btScalar& f){body->setCcdMotionThreshold(f);};
        inline void setCcdSweptSphereRadius(const btScalar& f){body->setCcdSweptSphereRadius(f);};

    protected:
        btRigidBody* body;
};

class RigideBox : public RigideObject
{
    public:
        RigideBox(float mass,btDiscreteDynamicsWorld* Wordl,btVector3 position, btVector3 size);
        ~RigideBox();
        void DrawGL();
        GLuint ListeAffichage;

    protected:
        btVector3 size;
    private:
        //static unsigned int Nb;
};

#endif
