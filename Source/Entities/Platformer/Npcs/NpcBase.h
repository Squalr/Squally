#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HexusEvents.h"
#include "Resources.h"
#include "Scenes/Hexus/Hexus.h"

using namespace cocos2d;

class NpcBase : public PlatformerEntity
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
