#pragma once
#include "Game.h"
#include "Tree.h"
#include "Stairs.h"
#include "Wall.h"
#include "Bear.h"


namespace BGE
{
	class Assignment1 : public Game{
	private:


		shared_ptr<Tree> tree;
		shared_ptr<Stairs> stairs;
		shared_ptr<Wall> wall;
		shared_ptr<Bear> bear;

	public:
		Assignment1();
		~Assignment1();
		bool Initialise();


	};

}