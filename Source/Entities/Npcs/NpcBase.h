#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class NpcBase : public Entity
{
protected:
	NpcBase();
	~NpcBase();

	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

	void update(float) override;

private:

	void onInteractButtonClick(MenuSprite* menuSprite);

	MenuSprite * interactButton;
};
