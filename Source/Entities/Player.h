#pragma once
#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	Player();
	~Player();

	void onEnter() override;
	void update(float) override;

protected:
	const float jumpSpeed = 144.0f;
	const float walkSpeed = 128.0f;

private:
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeListeners();
};

