#include "Bear.h"
#include "Utils.h"
using namespace BGE;

Bear::Bear(shared_ptr<PhysicsFactory> _physicsFactory)
{
	//allow for creation of objects
	physicsFactory = _physicsFactory;
	//give default position
	position = glm::vec3(0, 0, 0);
}

Bear::Bear(shared_ptr<PhysicsFactory> _physicsFactory, glm::vec3 pos)
{
	physicsFactory = _physicsFactory;
	position = pos;
}

Bear::~Bear()
{
}
bool Bear::Initialise()
{
	return true;
}

void Bear::createObject(float scale){

	//create torso
	body = createBody(scale);
	//create left arm
	armL = createLimb(scale, glm::vec3(position.x + 3, position.y + 5, position.z+5), 'l','f', body);
	//create rght arm
	armR = createLimb(scale, glm::vec3(position.x + (-3), position.y + 5, position.z + 5), 'r','f', body);
	//create left leg
	legL = createLimb(scale, glm::vec3(position.x + 3, position.y + 5, position.z + (-5)), 'l','b', body);
	//create right leg
	legR = createLimb(scale, glm::vec3(position.x + (-3), position.y + 5, position.z + (-5)), 'r','b', body);
	//create head and nose
	head = createHead(scale, glm::vec3(position.x + 0, position.y + 5, position.z + 8), body);
	//create hat
	topHat1 = createHat(scale, glm::vec3(position.x + 0, position.y + 8, position.z + 6), head);

}

//create torso
std::shared_ptr<PhysicsController> Bear::createBody(float scale)
{
	//return torso
	return physicsFactory->CreateBox(2 * scale, 5 * scale, 10 * scale,position *scale, glm::quat());
}

//create limb, hinge joint and apply motor
std::shared_ptr<PhysicsController> Bear::createLimb(float scale, glm::vec3 pos, char side, char face, std::shared_ptr<PhysicsController> body)
{
	std::shared_ptr<PhysicsController> limb = physicsFactory->CreateBox(2 * scale, 3 * scale, 7 * scale, pos*scale, glm::quat());

	//pivit position for the body
	btVector3 pivotA;
	//pivot position for the limb
	btVector3 pivotB;

	//if on left hand side
	if (side == 'l'){
		//if hinge is at front of body
		if (face == 'f'){
			pivotA = btVector3(2.5*scale, 0, 4 * scale);
		}
		//if hinge is at back of body
		if (face == 'b'){
			pivotA = btVector3(2.5*scale, 0, -4 * scale);
		}
		pivotB = btVector3(-1, 0, 0);
	}
	//if on right hand side
	else{
		//if hinge is at front of body
		if (face == 'f'){
			pivotA = btVector3(-2.5*scale, 0, 4 * scale);
		}
		//if hinge is at back of body
		if (face == 'b'){
			pivotA = btVector3(-2.5*scale, 0, -4 * scale);
		}
		
		pivotB = btVector3(1, 0, 0);
	}

	//create constraint between limb and body
	btHingeConstraint *arm_hinge = new btHingeConstraint(*body->rigidBody, *limb->rigidBody, pivotA, pivotB, btVector3(0, 0, 0), btVector3(1, 0, 0), true);

	//set limb limit
	arm_hinge->setLimit(0, 2);
	//set velocity and motor impulse of hinge
	arm_hinge->enableAngularMotor(true, 10 * scale, 10 * scale);
	//add hinge constraint
	physicsFactory->dynamicsWorld->addConstraint(arm_hinge);

	return limb;

}

//create head and nose and slider joint
std::shared_ptr<PhysicsController> Bear::createHead(float scale, glm::vec3 pos, std::shared_ptr<PhysicsController> body)
{
	//gap between head and nose
	glm::vec3 gap = glm::vec3(0, 0, .5);
	//create head
	head = physicsFactory->CreateBox(2 * scale, 2 * scale, 2 * scale, pos*scale, glm::quat());

	//fixed joint between head and body
	bodyTransform.setIdentity();
	headTransform.setIdentity();
	bodyTransform.setOrigin(btVector3(0, 0, 5 * scale));
	headTransform.setOrigin(btVector3(0, 0, -1 * scale));
	btFixedConstraint *neck_fixed = new btFixedConstraint(*body->rigidBody, *head->rigidBody, bodyTransform, headTransform);

	//create nose
	nose = physicsFactory->CreateSphere(.5*scale, (pos + gap)*scale, glm::quat());

	//slider constraint for the nose and body
	headTransform.setIdentity();
	noseTransform.setIdentity();
	headTransform.setOrigin(btVector3(0, 0, .5 * scale));
	noseTransform.setOrigin(btVector3(0, 0, 0));

	// Set rotation and axis to slide on
	headTransform.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 1, 0))));
	noseTransform.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 1, 0))));

	//create slider joint
	btSliderConstraint * nose_slider = new btSliderConstraint(*head->rigidBody, *nose->rigidBody, headTransform, noseTransform, true);

	//add constraints
	physicsFactory->dynamicsWorld->addConstraint(nose_slider);
	physicsFactory->dynamicsWorld->addConstraint(neck_fixed);


	return head;
}

//create hat and slider joint
std::shared_ptr<PhysicsController> Bear::createHat(float scale, glm::vec3 pos, std::shared_ptr<PhysicsController> head)
{
	//create base of hat
	topHat1 = physicsFactory->CreateCylinder(1 * scale, 1 * scale, pos*scale, glm::quat());
	//create top of hat
	topHat2 = physicsFactory->CreateCylinder(.5 * scale, 2 * scale, glm::vec3(pos.x * scale, (pos.y+2) * scale, pos.z * scale), glm::quat());

	//fixed constraint for constructing a top hat
	btTransform hat1;
	btTransform hat2;
	hat1.setIdentity();
	hat2.setIdentity();
	hat1.setOrigin(btVector3(0, 0 * scale, 0));
	hat2.setOrigin(btVector3(0, -2 * scale, 0));
	btFixedConstraint *tophat_con_fixed = new btFixedConstraint(*topHat1->rigidBody, *topHat2->rigidBody, hat1, hat2);

	//slider constraint for top hat on the head
	btTransform headTransform1;
	btTransform hatTransform;
	headTransform1.setIdentity();
	hatTransform.setIdentity();
	headTransform1.setOrigin(btVector3(0, 1 * scale, 0));
	hatTransform.setOrigin(btVector3(0, -1 * scale, 0));

	// Set rotation and axis to slide on
	headTransform1.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))));
	hatTransform.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0, 0, 1))));

	//create slider joint
	btSliderConstraint * hat_slider = new btSliderConstraint(*head->rigidBody, *topHat1->rigidBody, headTransform1, hatTransform, true);

	//add constraints
	physicsFactory->dynamicsWorld->addConstraint(tophat_con_fixed);
	physicsFactory->dynamicsWorld->addConstraint(hat_slider);

	return topHat1;
}

