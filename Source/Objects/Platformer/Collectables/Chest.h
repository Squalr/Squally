#pragma once

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;

class Chest : public GameObject
{
public:
	static Chest* create(cocos2d::ValueMap& properties);

	virtual void open();
	virtual void close();

	static const std::string MapKeyChest;

private:
	typedef GameObject super;
	Chest(cocos2d::ValueMap& properties);
	virtual ~Chest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	CollisionObject* interactCollision;
	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;
	InteractMenu* interactMenu;
	bool canInteract;

	std::string chestOpenEvent;
	std::string chestOpenArgs;

	static const std::string MapKeyCipherEvent;
};
