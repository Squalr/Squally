#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Resources.h"
#include "Collision/TileCollision.h"
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

	const float jumpSpeed = 320.0f;
	const float walkSpeed = 256.0f;
	const float gravity = 256.0f;
	const float hoverHeight = 96.0f;
};

