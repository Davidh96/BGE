#pragma once
#include "Game.h"

namespace BGE{
	class Bear : public GameComponent
	{
	private:
		btTransform bodyTransform;
		btTransform noseTransform;
		btTransform headTransform;

		glm::vec3 position;

		std::shared_ptr<PhysicsController> createBody(float scale);
		std::shared_ptr<PhysicsController> createLimb(float scale, glm::vec3 pos, char side, char face, std::shared_ptr<PhysicsController> body);
		std::shared_ptr<PhysicsController> createHead(float scale, glm::vec3 pos, std::shared_ptr<PhysicsController> body);
		std::shared_ptr<PhysicsController> createHat(float scale, glm::vec3 pos, std::shared_ptr<PhysicsController> head);

		shared_ptr<PhysicsFactory> physicsFactory;

		std::shared_ptr<PhysicsController> nose;
		std::shared_ptr<PhysicsController> head;
		std::shared_ptr<PhysicsController> body;
		std::shared_ptr<PhysicsController> armL;
		std::shared_ptr<PhysicsController> armR;
		std::shared_ptr<PhysicsController> legL;
		std::shared_ptr<PhysicsController> legR;
		std::shared_ptr<PhysicsController> tail;
		std::shared_ptr<PhysicsController> stabilizer;

		std::shared_ptr<PhysicsController> topHat1;
		std::shared_ptr<PhysicsController> topHat2;

	public:
		Bear(shared_ptr<PhysicsFactory> _physicsFactory);
		Bear(shared_ptr<PhysicsFactory> _physicsFactory,glm::vec3 pos);
		~Bear();
		bool Initialise();


		void createObject(float scale);

	};
	

}
