#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class EntityPetrificationBehavior : public AttachedBehavior
{
public:
	static EntityPetrificationBehavior* create(GameObject* owner);

	void unpetrify();

	static const std::string MapKey;

protected:
	EntityPetrificationBehavior(GameObject* owner);
	virtual ~EntityPetrificationBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	cocos2d::Vec2 displayOffset;
	
	cocos2d::Sprite* petrifiedSprite;
};
