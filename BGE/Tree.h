#pragma once
#include "Game.h"
namespace BGE{
	class Tree :public GameComponent
	{

	private:
		glm::vec3 position;
		int scale;
		shared_ptr<PhysicsFactory> physicsFactory;

	public:
		Tree(shared_ptr<PhysicsFactory> _physicsFactory,int _scale);
		Tree(shared_ptr<PhysicsFactory> _physicsFactory,glm::vec3 pos,int _scale);
		~Tree();
		bool Initialise();
		void createTree();

		
	};
}

