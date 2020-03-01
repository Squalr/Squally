#pragma once

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;
class MinMaxPool;

class ChestBase : public GameObject
{
public:

protected:
	ChestBase(cocos2d::ValueMap& properties, cocos2d::Size interactSize);
	virtual ~ChestBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void toggleInteractMenu();

	virtual void open();
	virtual void close();
	virtual void unlock();
	virtual void lock();
	virtual void onInteract();
	virtual void performUnlockAndGiveItems();

	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;

	MinMaxPool* chestPool;

private:
	typedef GameObject super;

	CollisionObject* interactCollision;
	InteractMenu* interactMenu;
	bool isOpen;
	bool isLocked;
	bool isPlayerColliding;

	std::string chestOpenArgs;

	static const std::string MapKeyPropertyRewardPool;
	static const std::string SaveKeyIsOpen;
};
