#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Entities/Player/Hover.h"
#include "Events/NavigationEvents.h"
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

	enum Wand
	{
		None,
		Stick,
		Snake,
		Ancient,
		Spider,
		Crystal,
		Dragon,
		Skeleton
	};

	void registerHackables();
	void onEnter() override;
	void update(float) override;
	void setFlippedX(bool newIsFlipped);
	void equipWand(Wand wand);

	bool isFlipped;
	bool canJump;

	InputManager* inputManager;
	Hover* hover;

	static const float playerScale;
};
