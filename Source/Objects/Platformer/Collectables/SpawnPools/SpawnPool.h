#pragma once

#include "Engine/Maps/GameObject.h"

class Collectable;

class SpawnPool : public GameObject
{
public:
	void setOwner(GameObject* owner);

	void trySpawnCollectable();

	static const std::string MapKeySpawnPool;
	static const std::string SaveKeySpawnCollected;

protected:
	SpawnPool(cocos2d::ValueMap& properties);
	virtual ~SpawnPool();

	void onEnter() override;
	virtual Collectable* spawnCollectable() = 0;

private:
	typedef GameObject super;
	
	void saveCollected();
	bool isCollected();

	GameObject* owner;
};
