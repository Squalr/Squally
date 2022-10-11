#pragma once

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class PlatformerObjectDeserializer;
class SpawnPool;

class BreakableBase : public HackableObject
{
public:

protected:
	BreakableBase(cocos2d::ValueMap& properties, cocos2d::CSize collisionSize, int requiredHits = 1);
	virtual ~BreakableBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void onBreak();
	SpawnPool* getSpawnPool();

	PlatformerObjectDeserializer* objectDeserializer = nullptr;
	cocos2d::Node* contentNode = nullptr;

private:
	typedef HackableObject super;

	CollisionObject* breakableCollision = nullptr;
	SpawnPool* spawnPool = nullptr;
	bool hasBroke = false;
};
