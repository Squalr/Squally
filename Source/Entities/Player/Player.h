#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Entities/Player/Hover.h"
#include "Objects/Collision/CategoryGroup.h"
#include "Input/InputManager.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	static Player * create();

	Size getSize() override;

	static int health;
	static Vec2 position;

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;
	bool hoverContactBegin(CollisionData data);
	bool hoverContactUpdate(CollisionData data);
	bool hoverContactEnd(CollisionData data);

private:
	Player();
	~Player();

	void registerHackables();
	void update(float) override;
	void setFlippedX(bool isFlipped);

	bool canJump;

	InputManager* inputManager;
	Hover* hover;

	Sprite* baseSprite;
	Sprite* mouthSprite;
	Sprite* eyesSprite;
	Sprite* armSprite;
	Sprite* wandSprite;

	static const float playerScale;
};
