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

protected:
	MayanDoor(cocos2d::ValueMap& properties);
	virtual ~MayanDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;
	void registerHackables() override;

private:
	typedef Portal super;

	void tryTakeGems();
	void tryUnlock();
	int runGemRed(int currentIndex);
	int runGemBlue(int currentIndex);
	int runGemPurple(int currentIndex);

	bool isUnlocking;
	int redGemAnswer;
	int blueGemAnswer;
	int purpleGemAnswer;
	
	MayanGemRed* redGem;
	MayanGemBlue* blueGem;
	MayanGemPurple* purpleGem;
	CollisionObject* turninHitbox;
	cocos2d::Sprite* doorArrow;
	cocos2d::Sprite* doorFrame;
	cocos2d::Node* doorContainer;
	cocos2d::Node* innerContainer;
	cocos2d::Sprite* door;

	WorldSound* doorOpenSound;

	Inventory* inventory;

	static const float DoorOpenDelta;
	static const std::string EventMayanDoorUnlock;
	static const std::string SaveKeyRedGem;
	static const std::string SaveKeyBlueGem;
	static const std::string SaveKeyPurpleGem;
	static const std::string SaveKeyRedGemAnswer;
	static const std::string SaveKeyBlueGemAnswer;
	static const std::string SaveKeyPurpleGemAnswer;
	static const std::string SaveKeyUnlocked;
};
