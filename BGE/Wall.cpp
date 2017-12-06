#include "Wall.h"
using namespace BGE;


Wall::Wall(shared_ptr<PhysicsFactory> _physicsFactory, int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	scale = _scale;

	//default size of 5x5
	length = 5;
	height = 5;

	//give random position
	float x1 = rand() % 200 - 100;
	float z1 = rand() % 200 - 100;
	position = glm::vec3(x1, 0, z1);
}

Wall::Wall(shared_ptr<PhysicsFactory> _physicsFactory, glm::vec3 pos, int _length, int _height, int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	position = pos;
	length = _length;
	height = _height;
	scale = _scale;
}


Wall::~Wall()
{
}

bool Wall::Initialise()
{
	return true;
}

void Wall::createWall()
{
	//create wall with specified length and height
	for (int i = 0; i < length; i++){
		for (int j = 0; j < height; j++){
			std::shared_ptr<PhysicsController> block = physicsFactory->CreateBox(2*scale, 4*scale, 2 * scale, glm::vec3((position.x +(2 * i))*scale, (position.y + (4*j))*scale, position.z*scale), glm::quat());
		}
	}
}