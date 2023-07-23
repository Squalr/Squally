#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;

class Trigger : public GameObject
{
public:
	static Trigger* create(cocos2d::ValueMap& properties);

	CollisionObject* getCollision();

	static const std::string MapKey;

protected:
	Trigger(cocos2d::ValueMap& properties);
	virtual ~Trigger();

	void onEnter() override;
	void initializeListeners() override;
	virtual void onCollide();

	bool wasActivated = false;
	bool multiTrip = false;
	bool saveState = false;

private:
	typedef GameObject super;

	CollisionObject* triggerCollision = nullptr;
	std::string endCollisionEvent;

	static const std::string PropertyEndEvent;
	static const std::string PropertySaveState;
	static const std::string PropertyMultiTrip;
};
