#include "Tree.h"
#include "Utils.h"
using namespace BGE;


Tree::Tree(shared_ptr<PhysicsFactory> _physicsFactory,int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	scale = _scale;

	//give random location
	float x1 = rand() % 200 - 100;
	float z1 = rand() % 200 - 100;
	position = glm::vec3(x1, 0, z1);
}

Tree::Tree(shared_ptr<PhysicsFactory> _physicsFactory,glm::vec3 pos,int _scale)
{
	//in order to create objects
	physicsFactory = _physicsFactory;
	position = pos;
	scale = _scale;
}


Tree::~Tree()
{
}

bool Tree::Initialise()
{
	return true;
}

void Tree::createTree()
{
	//crown of tree
	std::shared_ptr<PhysicsController> treeCrown = physicsFactory->CreateCylinder(5 * scale, 10 * scale, glm::vec3(position.x* scale, position.y + 20 * scale, position.z* scale), glm::quat(), false, true);
	//trunk of tree
	std::shared_ptr<PhysicsController> treeTrunk = physicsFactory->CreateBox(2 * scale, 10 * scale, 2 * scale, glm::vec3(position.x* scale, position.y + 9 * scale, position.z* scale), glm::quat());

	//create fixed constraint between crown and trunk of tree
	btTransform treeCrownTransform;
	btTransform treeTrunkTransform;
	treeCrownTransform.setIdentity();
	treeTrunkTransform.setIdentity();
	treeCrownTransform.setOrigin(btVector3(0, -4 * scale, 0));
	treeTrunkTransform.setOrigin(btVector3(0, 6 * scale, 0));
	btFixedConstraint *tree_fixed = new btFixedConstraint(*treeCrown->rigidBody, *treeTrunk->rigidBody, treeCrownTransform, treeTrunkTransform);
	//add constraint
	physicsFactory->dynamicsWorld->addConstraint(tree_fixed);


}
