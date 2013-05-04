#include "CreateObject.hpp"

#include "Object.hpp"


/// OBJECT
Object::Object(float mass,btDiscreteDynamicsWorld* World,btVector3 position)
{
    this->mass= mass;
    Program=NULL;
};

Object::~Object()
{
    delete MotionState;
    delete Shape;
}
/// RIGIDE OBJECT
RigideObject::RigideObject(float mass,btDiscreteDynamicsWorld* World,btVector3 position) : Object(mass,World,position)
{
    btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(position);

    MotionState=new btDefaultMotionState(Transform);
};

RigideObject::~RigideObject()
{
        delete MotionState;
    delete Shape;
    delete body;
}
/// RIGIDE BOX
 RigideBox::RigideBox(float mass,btDiscreteDynamicsWorld* World,btVector3 position, btVector3 size) : RigideObject(mass,World,position)
 {
    this->size = size;
    Shape = new btBoxShape(size);

    btVector3 localInertia(0,0,0);
    if (mass != 0.f)
        Shape->calculateLocalInertia( mass, localInertia);

    body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass, MotionState, Shape, localInertia));
    World->addRigidBody(body);
    RigideBox::ListeAffichage=MKBox();
   // ++Nb;
 };

RigideBox::~RigideBox()
{
//    --Nb;
   // if (Nb==0)
       delete MotionState;
    delete Shape;
        glDeleteLists(RigideBox::ListeAffichage, 1);
};

 void RigideBox::DrawGL()
 {
    /// TODO Ne pas afficher les objets non visibles
    /// TODO Ne pas faire les shader sur les objets loins
    btScalar matrix[16];
    MotionState->m_graphicsWorldTrans.getOpenGLMatrix(matrix);
    glPushMatrix();
    glMultMatrixf( matrix );
    glScalef(size[0],size[1],size[2]);//size
    if (Program)
    {
        Program->Bind();
        glCallList(RigideBox::ListeAffichage);//liste d'affichage
        //Program->Unbind();
    }
    else
        glCallList(RigideBox::ListeAffichage);//liste d'affichage

    glPopMatrix();
 };
