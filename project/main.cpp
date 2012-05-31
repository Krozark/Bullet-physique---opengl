#include "Fenettre.hpp"
#include <time.h>

int main ( int argc, char **argv )
{
	// On crée notre fenâtre grâce à SFML
    Fenettre Windows(sf::VideoMode( 1200, 900, 32 ), "SFML : Bullet physics");
    srand(time(NULL));

	/// box ///////////////////////////////////////////
	#define SIZEX   2
	#define SIZEY   2
	#define SIZEZ   2
    for (unsigned int j=0; j<10; ++j)
        for (unsigned int i=0; i<10;++i)
            for (unsigned int k=0;k<10;++k)
                Windows.AddRigidBox(btVector3(j*(2*SIZEX+SIZEX/10.0),i*(2*SIZEY+SIZEY/10.0),k*(2*SIZEZ+SIZEZ/10.0)),0.5L,btVector3(SIZEX,SIZEY,SIZEZ));
                //Windows.AddRigidBox(btVector3(j*(2*SIZEX+SIZEX/10.0),i*(2*SIZEY+SIZEY/10.0),k*(2*SIZEZ+SIZEZ/10.0)),(randRange(0,100)<=5)?0.f:0.5f,btVector3(SIZEX,SIZEY,SIZEZ));
    /// AFFICHER LA FENETTRE /////////////////////////
	Windows.RenderMe();
};
