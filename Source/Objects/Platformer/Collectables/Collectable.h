#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;
class LocalizedString;
class SmartAnimationSequenceNode;

class Collectable : public GameObject
{
public:
	static Collectable* create(cocos2d::ValueMap& properties);
	static Collectable* create();

	void onCollected(std::function<void()> onCollectedEvent);

protected:
	Collectable(cocos2d::ValueMap& properties);
	virtual ~Collectable();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* collectableNode;

private:
	typedef GameObject super;

	void disableCollection();

	CollisionObject* collectableCollision;

	bool isCollected;
	std::vector<std::function<void()>> collectionEvents;

	static const std::string SaveKeyIsCollected;
};
