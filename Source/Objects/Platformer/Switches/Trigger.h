#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;

class Trigger : public GameObject
{
public:
	static Trigger* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Trigger(cocos2d::ValueMap& properties);
	virtual ~Trigger();

	void onEnter() override;
	void initializeListeners() override;
	virtual void onCollide();

	bool wasActivated;
	bool multiTrip;
	bool saveState;

private:
	typedef GameObject super;

	CollisionObject* triggerCollision;

	static const std::string PropertySaveState;
	static const std::string PropertyMultiTrip;
};
