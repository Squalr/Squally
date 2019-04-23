#pragma once

#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class CollisionObject;
class InteractMenu;

class Chest : public SerializableObject
{
public:
	static Chest* create(cocos2d::ValueMap& initProperties);

	virtual void open();
	virtual void close();

	static const std::string MapKeyChest;

private:
	typedef SerializableObject super;
	Chest(cocos2d::ValueMap& initProperties);
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
