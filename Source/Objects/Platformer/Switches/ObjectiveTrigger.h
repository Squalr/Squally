#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class ObjectiveTrigger : public GameObject
{
public:
	static ObjectiveTrigger* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ObjectiveTrigger(cocos2d::ValueMap& properties);
	virtual ~ObjectiveTrigger();

	void initializeListeners() override;

private:
	typedef GameObject super;

	CollisionObject* triggerCollision;
};
