#pragma once
#include "Game.h"

namespace BGE{
	class Stairs:public GameComponent
	{
	private:
		int levels;
		int length;
		int scale;
		glm::vec3 position;
		shared_ptr<PhysicsFactory> physicsFactory;
	public:
		Stairs(shared_ptr<PhysicsFactory> _physicsFactory,int _scale);
		Stairs(shared_ptr<PhysicsFactory> _physicsFactory, glm::vec3 pos,int _levels,int _length,int _scale);
		~Stairs();
		bool Initialise();
		void createStairs();
		
		
	};

}
