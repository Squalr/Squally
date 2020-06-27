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

	void setCollectCooldown(float cooldown = 0.25f);
	void onCollected(std::function<void()> onCollectedEvent);

protected:
	Collectable(cocos2d::ValueMap& properties);
	virtual ~Collectable();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	virtual void hideCollectable();

	cocos2d::Node* collectableNode;
	CollisionObject* collectableCollision;

private:
	typedef GameObject super;

	void tryCollect();
	void disableCollection();

	bool isCollected;
	std::vector<std::function<void()>> collectionEvents;

	static const std::string SaveKeyIsCollected;

	float collectCooldown;
};
