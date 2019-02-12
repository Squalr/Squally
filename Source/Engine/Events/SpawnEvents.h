#pragma once
#include <string>

#include "cocos/math/Vec3.h"

namespace cocos2d
{
	class Node;
}

class SerializableLayer;
class SerializableObject;

class SpawnEvents
{
public:
	enum class SpawnMethod
	{
		Below,
		Above
	};

	struct RequestObjectSpawnArgs
	{
		cocos2d::Node* spawner;
		cocos2d::Node* objectToSpawn;
		cocos2d::Vec3 spawnPosition;
		SpawnMethod spawnMethod;

		RequestObjectSpawnArgs() : spawner(nullptr), objectToSpawn(nullptr), spawnMethod(SpawnMethod::Above) { }
		RequestObjectSpawnArgs(cocos2d::Node* spawner, cocos2d::Node* objectToSpawn, cocos2d::Vec3 spawnPosition, SpawnMethod spawnMethod) : spawner(spawner), objectToSpawn(objectToSpawn), spawnPosition(spawnPosition), spawnMethod(spawnMethod) { }
	};

	struct RequestObjectSpawnDelegatorArgs
	{
		SerializableLayer* sourceLayer;
		cocos2d::Node* spawner;
		cocos2d::Node* objectToSpawn;
		cocos2d::Vec3 spawnPosition;
		SpawnMethod spawnMethod;

		RequestObjectSpawnDelegatorArgs() : sourceLayer(nullptr), spawner(nullptr), objectToSpawn(nullptr), spawnMethod(SpawnMethod::Above) { }
		RequestObjectSpawnDelegatorArgs(SerializableLayer* sourceLayer, cocos2d::Node* spawner, cocos2d::Node* objectToSpawn, cocos2d::Vec3 spawnPosition, SpawnMethod spawnMethod) : sourceLayer(sourceLayer), spawner(spawner), objectToSpawn(objectToSpawn), spawnPosition(spawnPosition), spawnMethod(spawnMethod) { }
	};

	static void TriggerObjectSpawn(RequestObjectSpawnArgs args);
	static void TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs args);

	static const std::string SpawnObjectEvent;
	static const std::string SpawnObjectDelegatorEvent;
};
