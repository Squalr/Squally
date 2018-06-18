#pragma once
#include "cocos2d.h"

#include "Entities/Entity.h"
#include "Events/HexusEvents.h"
#include "Objects/Collision/CategoryGroup.h"
#include "Resources.h"
#include "Scenes/Minigames/Hexus/Hexus.h"

using namespace cocos2d;

class NpcBase : public Entity
{
protected:
	NpcBase(ValueMap* initProperties,
		std::string scmlResource,
		bool isFlying,
		Size size = Size(256.0f, 256.0f),
		float scale = 1.0f,
		Vec2 collisionOffset = Vec2(0.0f, 0.0f));
	~NpcBase();

	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

	void update(float) override;

protected:
	virtual void onInteractButtonClick(MenuSprite* menuSprite);
	virtual void initializeCardData();

	Deck* deck;

private:
	MenuSprite * interactButton;
};
