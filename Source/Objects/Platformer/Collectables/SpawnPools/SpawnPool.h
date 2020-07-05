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
	struct SpawnObjectEvent
	{
		float probability;
		std::function<Collectable*()> spawnFunc;

		SpawnObjectEvent(float probability, std::function<Collectable*()> spawnFunc) : probability(probability), spawnFunc(spawnFunc) { }
	};

	SpawnPool(cocos2d::ValueMap& properties);
	virtual ~SpawnPool();

	void onEnter() override;
	Collectable* spawnCollectable();
	void addSpawnEvent(SpawnObjectEvent spawnEvent);

	std::vector<SpawnObjectEvent> spawnEvents;

private:
	typedef GameObject super;
	
	void saveCollected();
	bool isCollected();

	GameObject* owner;
};
