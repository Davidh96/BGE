#include "Assignment1.h"
#include "Utils.h"
#include "Tree.h"
#include "Stairs.h"
using namespace BGE;

Assignment1::Assignment1()
{


}


Assignment1::~Assignment1()
{
}


bool Assignment1::Initialise(){
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();
	Attach(ground);
	Game::Initialise();

	Game::dynamicsWorld->setGravity(btVector3(0, -9.0f, 0));

	for (int i = 0; i < 3; i++){
		tree = make_shared<Tree>(physicsFactory, 1);
		tree->Initialise();
		tree->createTree();
	}

	stairs = make_shared<Stairs>(physicsFactory, glm::vec3(-10, 0, 20), 3, 3, 1);
	stairs->Initialise();
	stairs->createStairs();


	wall = make_shared<Wall>(physicsFactory, glm::vec3(20, 0, 10), 3, 4, 1);
	wall->Initialise();
	wall->createWall();

	bear = make_shared<Bear>(physicsFactory,glm::vec3(10,0,0));
	bear->Initialise();
	bear->createObject(1);


	return true;
}

