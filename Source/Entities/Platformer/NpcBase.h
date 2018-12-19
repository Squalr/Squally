#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Hexus/CardData/CardList.h"

class NpcBase : public PlatformerEntity
{
protected:
	NpcBase(ValueMap* initProperties,
		std::string scmlResource,
		PlatformerCollisionType collisionType,
		Size size = Size(256.0f, 256.0f),
		float scale = 1.0f,
		Vec2 collisionOffset = Vec2(0.0f, 0.0f));
	~NpcBase();

	void update(float) override;

protected:
	virtual void initializeCollisionEvents() override;
	virtual void onInteractButtonClick(MenuSprite* menuSprite);

private:
	MenuSprite* interactButton;
};
