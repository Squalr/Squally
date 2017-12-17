#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Resources.h"
#include "Collision/TileCollision.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	Player();
	~Player();

	void onEnter() override;
	void update(float) override;

	static int health;
	static Vec2 position;

protected:
	const float jumpSpeed = 320.0f;
	const float walkSpeed = 128.0f;

private:
	bool OnContactBegin(PhysicsContact &contact);
	bool OnContactPostSolve(PhysicsContact &contact);
	bool OnContactPreSolve(PhysicsContact &contact);
	bool OnContactSeparate(PhysicsContact &contact);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeListeners();
	bool canJump;
};

