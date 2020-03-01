#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
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

	static const std::string MapKeyMayanDoor;

protected:
	MayanDoor(cocos2d::ValueMap& properties);
	virtual ~MayanDoor();

	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;

private:
	typedef Portal super;

	void tryUnlock();

	bool isUnlocking;
	
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

	static const float DoorOpenDelta;
	static const std::string EventMayanDoorUnlock;
	static const std::string SaveKeyRedGem;
	static const std::string SaveKeyBlueGem;
	static const std::string SaveKeyPurpleGem;
	static const std::string SaveKeyUnlocked;
};
