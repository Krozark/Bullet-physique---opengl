#include "Fenettre.hpp"
#include "FreeFlyCamera.hpp"

#define GRAVITEE    -10.0f
#define MAXSHADER   2
ShaderProgram * Prog[MAXSHADER];

/*
class RenderTerrain : public btTriangleCallback
{
    public :
        RenderTerrain(){};
        void processTriangle(btVector3* triangle, int partId, int triangleIndex)
        {
            btVector3 diff1 = triangle[1] - triangle[0];
            btVector3 diff2 = triangle[2] - triangle[0];
            btVector3 normal = diff1.cross(diff2);
            normal.normalize();
            normal*=-1;

            glBegin(GL_TRIANGLES);
            glColor3f(1.0f,0.0f,0.0f);
            glNormal3d(normal.getX(),normal.getY(),normal.getZ());
            glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());

            glColor3f(1.0f,1.0f,0.0f);
            glNormal3d(normal.getX(),normal.getY(),normal.getZ());
            glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());

            glColor3f(0.0f,1.0f,1.0f);
            glNormal3d(normal.getX(),normal.getY(),normal.getZ());
            glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
            glEnd();
        }
};





RenderTerrain* test;
btDefaultMotionState *MotionState;

*/

Fenettre::Fenettre (sf::VideoMode Mode,std::string nom,float FrameTime) : sf::Window(Mode,nom,sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,sf::ContextSettings(32))
{
    SetFramerateLimit(FrameTime);
    Init();
};

Fenettre::Fenettre() : sf::Window()
{
    Init();
};

void Fenettre::Init()
{
    /// Initialisation d'OpenGL
    // On active la lumière 0
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
	// Quelques autres options OpenGL
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR);
	glEnable(GL_TEXTURE_2D);
    // Couleur de fond d'écran
    glClearColor(0.0,0.0,0.0,0);
	// l'espace d'affichage
	glViewport( 0, 0, 1200, 900 );
    glewInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 800.0/500.0, 0.001f, 1000.0f );

    /// Initialisation de Bullet
    CollisionConfiguration = new btDefaultCollisionConfiguration();
    Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
    Broadphase = new btDbvtBroadphase();
    SequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver;
    World = new btDiscreteDynamicsWorld(Dispatcher,Broadphase,SequentialImpulseConstraintSolver,CollisionConfiguration);
    World->setGravity( btVector3(0,GRAVITEE,0));


    btTransform Transform;
    Transform.setIdentity();
	Transform.setOrigin(btVector3(0,0,0));
    btDefaultMotionState* MotionState =new btDefaultMotionState(Transform);

    Terrain = new btStaticPlaneShape(btVector3(0,1,0),0);
    btVector3 localInertia(0,0,0);
    float mass=0;
    Terrain->calculateLocalInertia(mass,localInertia);
    btRigidBody *body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass, MotionState, Terrain, localInertia));
    World->addRigidBody(body);

    //test = new RenderTerrain();

    /// Initialisation des shaders

    SetActive();

    Prog[0] = new ShaderProgram("shader/mur.frag",sf::Shader::Fragment);
    Prog[0]->setTexture("Texture_Col","textures/Fieldstone.jpg");
    Prog[0]->setTexture("Texture_Normal","textures/FieldstoneBump.jpg");

    Prog[1] = new ShaderProgram("shader/mur.frag",sf::Shader::Fragment);
    Prog[1]->setTexture("Texture_Col","textures/redwall1_t.png");
    Prog[1]->setTexture("Texture_Normal","textures/redwall1_nm.png");


    /// Initialisation des truc perso
    ShowMouseCursor(false);
    camera = new FreeFlyCamera(btVector3(-5,20,0));
};

Fenettre::~Fenettre()
{
    delete CollisionConfiguration;
    delete Dispatcher;
    delete Broadphase;
    delete SequentialImpulseConstraintSolver;
    for (int i=ObjetsBt.size()-1; i>=0;--i)
        delete ObjetsBt[i];
    ObjetsBt.clear();

    free(World);
    for (int i=0; i< MAXSHADER;++i)
        delete Prog[i];

    delete camera;
};


void Fenettre::AddRigidBox(btVector3 position,btScalar mass,btVector3 size)
{
	RigideBox* Box =new RigideBox(mass,World,position,size);

    Box->SetShaderProgram(Prog[0]);

	ObjetsBt.push_back(Box);
};



void Fenettre::RenderScene()
{
    btScalar matrix[16];
    //MotionState->m_graphicsWorldTrans.getOpenGLMatrix(matrix);
    glPushMatrix();
    glMultMatrixf( matrix );
    //Terrain->processAllTriangles(test,btVector3(-100,0,-100),btVector3(100,0,100));
    glPopMatrix();
    glColor3f(1,1,0);
	for (int i=ObjetsBt.size()-1;i>=0;--i)
	{
		ObjetsBt[i]->DrawGL();
	}
};

void Fenettre::RenderMe()
{
   #if FRAME_TIME <= 0
    sf::Clock clock;
    #endif
    bool run = false;
    PositionCamera();
    while(IsOpen())
	{
        sf::Event event;
        while(PollEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                Close();
            }
            else if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Escape))
            {
                Close();
            }
            else if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Space))
            {
                run = !run;
            }
            else if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::R))
            {
                camera->setPosition(btVector3(-100,50,0));
            }
            // Adjust the viewport when the window is resized
            else if (event.Type == sf::Event::Resized)
            {
                glViewport(0, 0, event.Size.Width, event.Size.Height);
            }
            else if (run && event.Type == sf::Event::MouseMoved)
            {
                camera->MouseMoved();
            }
            else if (run && event.Type == sf::Event::MouseWheelMoved)
            {
                camera->MouseWheelMoved(event);
            }
            else if (run && event.Type == sf::Event::MouseButtonPressed)
            {
                shootBox(camera->GetCible());
            }

        }

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Update dynamics
		if (run)
		{
           #if FRAME_TIME <= 0
            World->stepSimulation(clock.GetElapsedTime());
            camera->animate(clock.GetElapsedTime());
            #else
            World->stepSimulation(1.0f/FRAME_TIME);
            camera->animate(1.0f/FRAME_TIME);
            #endif

            PositionCamera();
		}

		RenderScene();
		glFlush();
		Display();
	}
};

void Fenettre::PositionCamera()
{
    // Mode perspective
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->look();
};

void Fenettre::shootBox(const btVector3& destination)
{
    if (World)
	{
        btVector3 camPos = camera->GetPosition();
        btVector3 linVel(destination[0]-camPos[0],destination[1]-camPos[1],destination[2]-camPos[2]);
		linVel.normalize();
		linVel*=1000.0f; //vitesse

        double size =1;
	    RigideBox* Box =new RigideBox(10.L,World,camPos,btVector3(size,size,size));
	    Box->SetShaderProgram(Prog[1]);
	    //Box->SetShaderProgram(Prog[randRange(0,MAXSHADER)]);
	    Box->setLinearFactor(btVector3(1,1,1));
	    Box->setOrigin(camPos);
        Box->setRotation(btQuaternion(0,0,0,1)); //angle de base
	    Box->setLinearVelocity(linVel);
	    Box->setAngularVelocity(btVector3(25,25,25)); //rotation
	    Box->setCcdMotionThreshold(size/2.0f);
	    Box->setCcdSweptSphereRadius(0.9f);

        ObjetsBt.push_back(Box);


	}
}
