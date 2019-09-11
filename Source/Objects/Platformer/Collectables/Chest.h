#pragma once

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;

class Chest : public GameObject
{
public:

protected:
	Chest(cocos2d::ValueMap& properties);
	~Chest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void toggleInteractMenu();

	virtual void open();
	virtual void close();
	virtual void unlock();
	virtual void lock();
	virtual void onInteract() = 0;

private:
	typedef GameObject super;

	CollisionObject* interactCollision;
	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;
	InteractMenu* interactMenu;
	bool isLocked;
	bool isPlayerColliding;

	std::string chestOpenArgs;
};
