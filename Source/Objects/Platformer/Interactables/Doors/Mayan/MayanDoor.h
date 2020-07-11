#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class RegisterStone;
class WorldSound;

class MayanDoor : public Portal
{
public:
	static MayanDoor* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;
	static const std::string MapEventPush;
	static const std::string MapEventPop;
	static const std::string MapEventPopRet;
	static const std::string PropertyRegister;
	static const std::string PropertyValue;
	static const std::string MapEventLockInteraction;
	static const std::string MapEventUnlockInteraction;
	static const std::string MapEventResetPuzzle;

protected:
	MayanDoor(cocos2d::ValueMap& properties);
	virtual ~MayanDoor();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;

	void discoverStones();
	void tryUnlock();

	bool isUnlocking;
	std::vector<RegisterStone*> registerStones;
	
	cocos2d::Sprite* doorArrow;
	cocos2d::Sprite* doorFrame;
	cocos2d::Node* doorContainer;
	cocos2d::Node* innerContainer;
	cocos2d::Sprite* door;
	WorldSound* doorOpenSound;

	static const float DoorOpenDelta;
	static const std::string EventMayanDoorUnlock;
	static const std::string SaveKeyUnlocked;
};
