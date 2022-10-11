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
	static const std::string MapEventPuzzleComplete;

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

	bool isUnlocking = false;
	std::vector<RegisterStone*> registerStones;
	
	cocos2d::Sprite* doorArrow = nullptr;
	cocos2d::Sprite* doorFrame = nullptr;
	cocos2d::Node* doorContainer = nullptr;
	cocos2d::Node* innerContainer = nullptr;
	cocos2d::Sprite* door = nullptr;
	WorldSound* doorSound2Units = nullptr;
	WorldSound* doorSound3Units = nullptr;
	WorldSound* doorSound4Units = nullptr;
	WorldSound* doorSound5Units = nullptr;
	WorldSound* doorSound6Units = nullptr;
	WorldSound* doorOpenSound = nullptr;

	static const float DoorOpenDelta;
	static const std::string EventMayanDoorUnlock;
	static const std::string SaveKeyUnlocked;
};
