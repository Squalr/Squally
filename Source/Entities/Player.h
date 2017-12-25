#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Resources.h"
#include "Collision/TileCollision.h"

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

	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeKeyMap();
	void InitializeListeners();

	std::unordered_map<EventKeyboard::KeyCode, bool> pressedKeys;
	bool canJump;

	const float jumpSpeed = 320.0f;
	const float walkSpeed = 128.0f;
};

