#pragma once
#include <mutex>
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Entities/Entity.h"
#include "Entities/Player/Hover.h"
#include "Events/NavigationEvents.h"
#include "Objects/Collision/CategoryGroup.h"
#include "Resources.h"

using namespace cocos2d;

class Player : public Entity
{
public:
	static Player * create();
	static Player * getInstance();

	Size getSize() override;

	static int health;

	static const std::string KeySquallyProperty;

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
	void onEnter() override;
	void update(float) override;
	void setFlippedX(bool newIsFlipped);

	bool isFlipped;
	bool canJump;

	InputManager* inputManager;
	Hover* hover;

	static const float playerScale;
	static Player* playerInstance;
};
