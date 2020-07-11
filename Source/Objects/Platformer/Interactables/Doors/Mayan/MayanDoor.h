#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class Inventory;
class MayanGemBlue;
class MayanGemPurple;
class MayanGemRed;
class WorldSound;

class MayanDoor : public Portal
{
public:
	static MayanDoor* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;
	static const std::string MapEventResetPuzzle;
	static const std::string MapEventPush;
	static const std::string MapEventPop;
	static const std::string MapEventPopRet;
	static const std::string PropertyRegister;
	static const std::string PropertyValue;

protected:
	MayanDoor(cocos2d::ValueMap& properties);
	virtual ~MayanDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;

	void loadGems();
	void tryUnlock();
	int runGemRed(int currentIndex);
	int runGemBlue(int currentIndex);
	int runGemPurple(int currentIndex);

	bool isUnlocking;
	
	cocos2d::Sprite* doorArrow;
	cocos2d::Sprite* doorFrame;
	cocos2d::Node* doorContainer;
	cocos2d::Node* innerContainer;
	cocos2d::Sprite* door;

	WorldSound* doorOpenSound;

	Inventory* inventory;

	static const float DoorOpenDelta;
	static const std::string EventMayanDoorUnlock;
	static const std::string SaveKeyUnlocked;
};
