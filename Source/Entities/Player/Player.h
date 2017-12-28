#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Collision/CollisionGroup.h"
#include "Input/InputManager.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	static Player * create();

	static int health;
	static Vec2 position;

protected:

private:
	Player();
	~Player();

	void update(float) override;

	bool canJump;

	InputManager* inputManager;
	PhysicsBody* hoverPhysicsBody;
	Node* hoverNode;

	const float hoverHeight = 96.0f;
};
