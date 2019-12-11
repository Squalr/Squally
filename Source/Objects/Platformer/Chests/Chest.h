#pragma once

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;
class MinMaxPool;

class Chest : public GameObject
{
public:

protected:
	Chest(cocos2d::ValueMap& properties);
	virtual ~Chest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void toggleInteractMenu();

	virtual void open();
	virtual void close();
	virtual void unlock();
	virtual void lock();
	virtual void onInteract() = 0;

	MinMaxPool* chestPool;

private:
	typedef GameObject super;

	CollisionObject* interactCollision;
	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;
	InteractMenu* interactMenu;
	bool isOpen;
	bool isLocked;
	bool isPlayerColliding;

	std::string chestOpenArgs;

	static const std::string MapKeyPropertyRewardPool;
	static const std::string SaveKeyIsOpen;
};
