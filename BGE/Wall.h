#pragma once
#include "Game.h"

namespace BGE{
	class Wall :public GameComponent
	{
	private:
		int scale;
		int length;
		int height;
		glm::vec3 position;
		shared_ptr<PhysicsFactory> physicsFactory;
	public:
		Wall(shared_ptr<PhysicsFactory> _physicsFactory, int _scale);
		Wall(shared_ptr<PhysicsFactory> _physicsFactory, glm::vec3 pos, int _length, int _height,int _scale);
		~Wall();
		bool Initialise();
		void createWall();
		
	};

}
