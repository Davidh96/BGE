#include "Stairs.h"
#include "Utils.h"
using namespace BGE;


Stairs::Stairs(shared_ptr<PhysicsFactory> _physicsFactory,int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	scale = _scale;
	//default values
	levels = 5;
	length = 10;
	
	//give random location
	float x1 = rand() % 200 - 100;
	float z1 = rand() % 200 - 100;
	position = glm::vec3(x1, 0, z1);
}

Stairs::Stairs(shared_ptr<PhysicsFactory> _physicsFactory, glm::vec3 pos, int _levels, int _length,int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	position = pos;
	levels = _levels;
	length = _length;
	scale = _scale;
}


Stairs::~Stairs()
{
}

bool Stairs::Initialise()
{
	return true;
}

void Stairs::createStairs()
{
	//create stairs of specified length and amount of levels
	for (int i = 0; i < length; i++){
		for (int j = 0; j < levels; j++){
			std::shared_ptr<PhysicsController> block = physicsFactory->CreateBox(2 * scale, 0.2f + (j)*scale, 2 * scale, glm::vec3((position.x - (2 * i))*scale, position.y*scale, (position.z + (2 * j))*scale), glm::quat());
		}
	}

}
